#include <stdio.h>

/* print Fahrenheit-Celsius table       
 * for fahr = 0, 20, ..., 300 */   

main()   
{     
    int lower = 0;      /* lower limit of temperature scale */     
    int upper =200;    /* upper limit */     
    int step = 20;      /* step size */
    float celsius = lower;     
    float fahr;

    fprintf(stdout, "Celsius to Fahrenheit conversion\n ");
    
    

    while (celsius <= upper) 
    {         
        fahr = (celsius * (9.0/5.0)) + 32;
	printf("%.1f\t%.1f\n", celsius, fahr);         
	celsius +=  step;     
    }   
}
