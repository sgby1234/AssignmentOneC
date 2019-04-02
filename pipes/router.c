

/*C----------------------------------------------------------------------------
  router
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  NAME
    @(#)   router - a simple routing program

  SYNOPSIS
    router in_file wfd1 wfd2
           in_file - input file
           wfd1    - write file descriptor 1
           wfd2    - write file descriptor 2

  DESCRIPTION
    router reads a line at a time from in_file
    sleeps for a specified period
    then forwards the line to the specified pipe

    Each line (as far as router is concerned) is of the form:
       {1|2}  num_seconds_to_nap  text
---------------------------------------------------------------------C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parent.h"

void
main(int argc, char *argv[])
{
    static char buffer[BUFSIZ];
    FILE *ifp = stdin;
    int  num1 = 0;
    int  num2 = 0;
    int  len  = 0;
    int  who  = -1;
    int  nap  = 0;

    fprintf(stdout, "%s checking in\n", argv[0]);

    if (argc < 4)
    {
        fprintf(stderr, "%s:  exiting on faulty invocation\n", *argv);
        exit(1);
    }
    else
    {
        fprintf(stdout, "\tinput file: %s   out channels %s & %s\n", argv[1], argv[2], argv[3]);
    }

    if ( NULL == (ifp = fopen(argv[1], "r"))) /* cannot open input file */
    {
        perror(argv[0]);
        exit(2);
    }

    num1 = atoi(argv[2]);
    num2 = atoi(argv[3]);
    /* fprintf(stdout, "%s:   num1 = %d\t num2 = %d\n", argv[0], num1, num2); */

    while (fgets(buffer, BUFSIZ, ifp))
    {
        if (2 != sscanf(buffer, "%d %d", &who, &nap)
              ||
            who != 1  &&  who != 2
              ||
            nap < 0)
        {
            fprintf(stderr, "%s bad input: |%s|\n", argv[0], buffer);
            continue;  /* ignore nonstandard input */
        }
        fprintf(stdout, "%s:  processing who = %d\t nap = %d\t buf = |%s|\n",
                         argv[0],              who,       nap,        buffer + OFF_2);

        sleep(nap);
        len = strlen(buffer + OFF_2);
        if ( 1 == who)
        {
            if (-1 == write(num1, buffer + OFF_2, len))
            {
                perror(argv[0]);
            }
        }
        else if (-1 == write(num2, buffer + OFF_2, len))
        {
            perror(argv[0]);
        }
    }

    exit(0);
}
/*----------------------- end of file --------------------------------*/
 
