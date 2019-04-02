#include <stdio.h>

/* print Fahrenheit-Celsius table       
 * for fahr = 0, 20, ..., 300 */   

main()   
{     
    int lower = 0;      /* lower limit of temperature scale */     
    int upper = 100;    /* upper limit */     
    int step = 5;      /* step size */
    int celsius = lower;     
    int fahr;

    fprintf(stdout, "Fahrenheit to Celsius conversion");
    
    

    while (celsius <= upper) 
    {         
        fahr = (celsius * (9/5)) + 32;
	printf("%d\t%d\n", celsius, fahr);         
	celsius +=  step;     
    }   
}
