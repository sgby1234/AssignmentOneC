#include <stdio.h>

void main(int argc, char *argv[])
{
    static double dar[8] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    static int    iar[8] = { 1,   2,   3,   4,   5,   6,   7,   8 };
    double *pd = dar;
    int    *pi = iar;

    fprintf(stdout, "pd  = %4x\t pd+1   = %4x\n",
                           pd,            pd+1);
    fprintf(stdout, "*pd = %4.1f\t*(pd+1) = %4.1f\n\n",
		          *pd,             *(pd+1));

    fprintf(stdout, "pi  = %4x\t pi+1   = %4x\n",
	                   pi,            pi+1);
    fprintf(stdout, "*pi = %4d\t*(pi+1) = %4d\n\n",
                          *pi,           *(pi+1));


    fprintf(stdout, "traversing dar with pointers to double:\n");
    int ix = 0;
    pd = dar;
    for (ix = 0; ix < 8; ++ix, ++pd)
    {
        fprintf(stdout, "pd = %4x\t, *pd = %4.1f\n", pd, *pd);		
    }

    fprintf(stdout, "\n\ntraversing dar with pointers to int:\n");
    ix = 0;
    pi = (int *)dar;
    for (ix = 0; ix < 16; ++ix, ++pi)
    {
         fprintf(stdout, "pi = %4x\t, *pi = %d\n", pi, *pi);		
    }
}
/*------------------------ end of file -------------------------------*/
