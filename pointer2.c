#include <stdio.h>
void main(int argc, char *argv[])
{
    char bytes[127];
    /* load them: */
    for (int ch = 0; ch < 96; ++ch)
    {
        bytes[ch] = ch+32;
    }

    /* chars */
    char *chp_bytes = bytes;
    int ii = 0;
    fprintf(stdout, "chars:\n");
    while (*chp_bytes > 0)
    {
         fprintf(stdout, "%c (%d)\t", *chp_bytes++, ii++ );
    }

    /* string */
    chp_bytes = bytes;
    fprintf(stdout, "\nstring:\n");
    fprintf(stdout, "%s",  chp_bytes);

    /* ints */
    int *intp_bytes = (int *)bytes;
    ii = 0;
    fprintf(stdout, "\nints:\n");
    while (*intp_bytes > 0)
    {
        fprintf(stdout, "%d (%d)\t", *intp_bytes++, ii++ );
    }

    /* longs */
    long *lngp_bytes = (long *)bytes;
    ii = 0;
    fprintf(stdout, "\nlongs:\n");
    while (*lngp_bytes > 0)
    {
        fprintf(stdout, "%ld (%d)\t", *lngp_bytes++, ii++ );
    }

    /* doubles */
    double *dblp_bytes = (double *)bytes;
    ii = 0;
    fprintf(stdout, "\ndoubles:\n");
    while (*dblp_bytes > 0)
    {
        fprintf(stdout, "%g (%d)\t", *dblp_bytes++, ii++ );
    }
}

