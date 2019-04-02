/*---------------------------------------------------------------------
  * timestamp - return hh:mm:ss string representing current time
---------------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char * timestamp()
{
        long clock = time((long *)0); /* seconds since ??? */
        char *a_time = ctime(&clock); /* converted to a timestamp */
        static char hhmmss[9];        /* buffer to hold hh:mm:ss  */

        strncpy(hhmmss, a_time + 11, 8);
        hhmmss[8] = '\0'; /* truncate year etc */
        return hhmmss;
}