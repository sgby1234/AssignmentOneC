#ifndef LPNMAX
#define LPNMAX 128                      /* MAX Length of Path Name    */
#endif

/* string to signal end of router's input */
#define ALL_DONE "ALL DONE\0"

#define OFF_1   3    /* offset of the first number in text */
#define OFF_2   6    /* offset of the secnd number in text */
#define OFF_3   9    /* offset of the actual text          */
/* example of text first processed by router
   (with a ruler and explanation):
   01234567890123456789.....................................
   1  9  2  message 1 to procpipe1 with a wait of 2 seconds
   \  \  \  \
    \  \  \  --- actual message echoed by procpipe
     \  \  \
      \  \  ---- nap duration for procpipe
       \  \
        \  ----- nap duration for router
         \
          ------ message meant for the first procpipe sibling
*/

/*----------------------- end of file --------------------------------*/
