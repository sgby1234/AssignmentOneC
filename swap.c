#include <stdio.h>

static void swap_bad (int, int);
static void swap_good(int *, int *);

void
main(void)
{
   int one = 1;
   int two = 2;

   fprintf(stdout,"initial values:         %d, %d\n", one, two);

   swap_bad(one,two);
   fprintf(stdout,"values after swap_bad:  %d, %d\n", one, two);

   swap_good(&one,&two);
   fprintf(stdout,"values after swap_good: %d, %d\n", one, two);

}
/*--------------------------------------------------------------------*/
static void
swap_bad(int aa, int bb)
{
   int tmp = aa;

   aa = bb;
   bb = tmp;
}

/*--------------------------------------------------------------------*/
static void
swap_good(int *aa, int *bb)
{
   int tmp = *aa;

   *aa = *bb;
   *bb = tmp;
}

/*------------------------ end of file -------------------------------*/

