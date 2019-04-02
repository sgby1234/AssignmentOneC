/*C---------------------------------------------------------------------
  parent
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  NAME
      parent - a model of parent process of children communicating
               via pipes

  SYNOPSIS
      parent [-i input file]
             [-1 output file of first child]
             [-2 output file of second child]

  DESCRIPTION
      parent process opens two communication pipes
      forks three children and waits
      when any of the children terminate,
      the remaining children are killed 15 (SIGTERM) and the parent exits

      The goal is  to establish a communication link  among  the children
      as depicted below.

      The eldest child acts as a message router.
      It listens for ascii input of the type:
         {1|2}  num1  num2  line_text,
         with  num1 beginning in column 3,
               num2 beginning in column 6, and
               line_text beginning in column 9
               (both nums to be exactly 2 digits.)
         If the leading number is 1,  the line beginning with num2 is passed
         to the second child after a wait of num1 seconds.  If it is 2, then
         it is passed  to the third child  (after the wait of num1 seconds).

         Each  of  the younger  children  sleeps  for the number of  seconds
         specified  by  num2  (all these sleeps  are introduced  in order to
         simulate procssing,  perhaps leading to various  scenarios  of pipe
         clogging) and then writes the rest of the line  (beginning with the
         first nonwhite space after the num) to its output file.   These two
         siblings of the first child execute procpipe overlay.

     When the router detects the end of its input stream, it sends a request
     to terminate to both of its procpipe siblings.

                             /-----------------\
                             |     parent      |
                             \-----------------/
                               |      |      |
                             fo|rk  fo|rk  fo|rk
                               |      |      |
                    ----------/       |       \--------
                   /                  |                \
                   |              /--------\           |
           /-------------\  pipe1 |        |           |
           |             =========> child2 |-->file_1  |
           |             |        |        |           |
           |   child1    |        \--------/      /--------\
           |             |                        |        |
           |             =========================> child3 |-->file_2
           \-------------/  pipe2                 |        |
                                                  \--------/

---------------------------------------------------------------------C*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "parent.h"

static void propt(int, char * [], char [], char [], char []);
extern char * timestamp();

void
main(int argc, char *argv[])
{
    static char in_file_name[LPNMAX] = "stdin";   /* input for child 1 */
    static char o1_file_name[LPNMAX] = "stdout";  /* output of child 2 */
    static char o2_file_name[LPNMAX] = "stdout";  /* output of child 3 */
           int  pipe1[2];                /* pipe between child 1 and 2 */
           int  pipe2[2];                /* pipe between child 1 and 3 */
           int  pid1;                    /* pid of child 1             */
           int  pid2;                    /* pid of child 2             */
           int  pid3;                    /* pid of child 3             */

    fprintf(stdout, "%s :  %s checking in\n", timestamp(), argv[0]);
    fflush(stdout);

   /*
   ** process command line arguments and open pipes
   ** if anything fails, then print error and exit
   */
   propt(argc, argv, in_file_name, o1_file_name, o2_file_name);
   if (-1 == pipe(pipe1)  ||  -1 == pipe(pipe2))
   {
       perror(argv[0]);
       exit(1);
   }

   fprintf(stdout, "%s :  %s ready to fork\n", timestamp(), *argv);
   fflush(stdout);

   /*
   ** fork the first child (router)
   */
   if (-1 == (pid1 = fork()))
   {
        perror(argv[0]);
        exit(2);
   }
   else if (0 == pid1)  /* child 1:  router */
   {
       /*
       ** close read channels
       */
       if (-1 == close(pipe1[0])  ||  -1 == close(pipe2[0]))
       {
           perror(argv[0]);
           exit(3);
       }

       /*
       ** set up and execute router child
       */
       char wfd1[5]; /* write file descriptor 1 saved as a string */
       char wfd2[5]; /* write file descriptor 2 saved as a string */
       sprintf(wfd1, "%d", pipe1[1]);
       sprintf(wfd2, "%d", pipe2[1]);
       execlp("router", "router", in_file_name, wfd1, wfd2, NULL);
       /* the only way to get to the next line is for execlp to fail */
       fprintf(stderr, "exec router failed\n");
       exit(4);
   }

   /*
   ** fork the second child (procpipe)
   */
   else if (-1 == (pid2 = fork()))
   {
        perror(argv[0]);
        kill(pid1, SIGTERM);
        exit(5);
   }
   else if (0 == pid2)  /* child 2:  procpipe */
   {
       /*
       ** close unused pipe channels
       */
       if (-1 == close(pipe1[1])     /* close write channel of pipe 1 */
              ||
           -1 == close(pipe2[0])     /* close entire pipe 2 */
              ||
           -1 == close(pipe2[1]))
       {
           perror("problem closing channels");
           exit(6);
       }

       /*
       ** prepare read channel command line argument
       */
       char rfd1[5]; /* read file descriptor 1 */
       sprintf(rfd1, "%d", pipe1[0]);

       /*
       ** execute procpipe 1 child
       */
       execlp("procpipe", "procpipe", rfd1, o1_file_name, NULL);
       /* the only way to get to the next line is for execlp to fail */
       fprintf(stderr, "exec procpipe 1 failed\n");
       exit(8);
   }

   /*
   ** fork the third child (procpipe)
   */
   else if (-1 == (pid3 = fork()))
   {
       perror("third fork failed");
       kill(pid1, SIGTERM);
       kill(pid2, SIGTERM);
       exit(9);
   }
   else if (0 == pid3)  /* child 3:  procpipe 2 */
   {
       /*
       ** close unused pipe channels
       */
       if (-1 == close(pipe2[1])     /* close write channel of pipe 2 */
              ||
           -1 == close(pipe1[0])     /* close entire pipe 1 */
              ||
           -1 == close(pipe1[1]))
       {
           perror("problem closing channels");
           exit(10);
       }

       /*
       ** prepare read channel command line argument
       */
       char rfd2[5]; /* read file descriptor 2 */
       sprintf(rfd2, "%d", pipe2[0]);

       /*
       ** execute procpipe 2 child
       */
       execlp("procpipe", "procpipe", rfd2, o2_file_name, NULL);
       /* the only way to get to the next line is for execlp to fail */
       fprintf(stderr, "exec procpipe 2 failed\n");
       exit(12);
   }


   /*
   ** parent waits for all the children to terminate
   */
   int nr_running_children = 3;
   int pid_terminated = 0;
   while (nr_running_children > 0)
   {
        /* we do not care why the child terminated */
        pid_terminated = wait((int *)0);
        --nr_running_children;
        fprintf(stdout, "%s child with pid %d terminated\n",
                         timestamp(),      pid_terminated);
        fprintf(stdout, "%d  children still running\n",
                         nr_running_children);
        fflush(stdout);
   }

   fprintf(stdout, "%s :  all children are gone!\n", timestamp());
   fprintf(stdout, "%s :  parent exiting 0\n");
   exit(0);
}
/*--------------------------------------------------------------------*/
static void
propt(int argc, char *argv[], char inf[], char of1[], char of2 [])
{
    extern char *optarg;
    int ch;

    while (EOF != (ch = getopt(argc, argv, "i:1:2:")))
    switch (ch)
    {
        case 'i' :  strncpy(inf, optarg, LPNMAX);   break;
        case '1' :  strncpy(of1, optarg, LPNMAX);   break;
        case '2' :  strncpy(of2, optarg, LPNMAX);   break;
    }
}
/*----------------------- end of file --------------------------------*/
