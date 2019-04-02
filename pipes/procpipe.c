/*C--------------------------------------------------------------------
  procpipe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  NAME
    procpipe - a simple process sitting on a pipe

  SYNOPSIS
    procpipe inp_fid out_file
             inp_fid  - input file descriptor (pipe read channel)
             out_file - output file name

  DESCRIPTION
    procpipe reads from a pipe
    sleeps for a specified period
    then forwards the text to out_file

    Each transmission (as far as procpipe is concerned) is of the form:
    num_seconds_to_nap  text

    Once ALL_DONE message is received, the process exits

---------------------------------------------------------------------C*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parent.h"


void
main(int argc, char *argv[])
{
    static char buffer[BUFSIZ];    /* private I/O char buffer  */
    FILE *ofp = stdout;            /* output file pointer      */
    int  len  = 0;                 /* read/write len indicator */
    int  nap  = 0;                 /* nap time in seconds      */
    int  nwr  = 0;                 /* number of bytes read     */
    int  nrs  = 0;                 /* number of fields scanned */
    int  pid  = getpid();          /* my process id            */

    if (argc < 3)
    {
        fprintf(stderr, "%s:  exiting on faulty invocation\n", *argv);
        exit(1);
    }

    fprintf(stdout,
            "%s :  %s (PID: %d) reading from %s,  writing to %s\n",
             timestamp(),
                   argv[0], pid,             argv[1],        argv[2]);
    fflush(stdout);


    int ifd = atoi(argv[1]);    /* input file descriptor         */
                                /* converted from argv[1] string */

    if (NULL == (ofp = fopen(argv[2], "w"))) /* cannot open output */
    {
         perror(argv[0]);
         exit(2);
    }

    do
    {
        if (-1 == (len = read(ifd, buffer, BUFSIZ)))
        {
            perror(argv[0]);
        }
        else if (len > OFF_1)
        {
            fprintf(stdout, "%s :  %s %d ready to process |%s|\n",
                             timestamp(),
                                   argv[0],
                                      pid,                 buffer);
            fflush(stdout);

            /* check if this is a call to terminate */
            if (!strncmp(ALL_DONE, buffer, 8))
            {
                /* got marching orders */
                fprintf(stdout, "%s :  %s %d received %s\n",
                                 timestamp(),
                                       argv[0],
                                          pid,        ALL_DONE);
                fflush(stdout);
                break; /* do */
            }


            /* have a legit message, extract nap duration: */
            if (1 == (nrs = sscanf(buffer, "%d", &nap)))
            {
                    fprintf(stderr, "\t\t%s: procpipe %d nap = %d\n",
                                         timestamp(), pid,     nap);
                    unsigned ret_sleep = sleep(nap);
                    fprintf(stderr, "\t\t%s: procpipe %d ret_sleep = %u\n",
                                         timestamp(), pid,          ret_sleep);


                fprintf(ofp, "%s: %s\n", timestamp(), buffer + OFF_1);
                fflush(ofp);
            }
            else
            {
                fprintf(stderr, "%s %d scanned %d nap times\n", argv[0], pid, nrs);
            }

            /*
             * check if ALL_DONE was "appended"
             * to the legitimate message just processed
             * */
            if (NULL != strstr(buffer, ALL_DONE))
            {
                fprintf(stdout, "%s :  %s %d received mbedded %s\n",
                                 timestamp(),
                                       argv[0],
                                          pid,                ALL_DONE);
                fflush(stdout);
                break; /* do */
           }
        }
    } while (len > 0);

    exit(0);
}

/*----------------------- end of file --------------------------------*/
