#include <stdio.h>

/* print Fahrenheit-Celsius table       
 * for fahr = 0, 20, ..., 300 */   

main()   
{     
    int lower = 0;      /* lower limit of temperature scale */     
    int upper = 300;    /* upper limit */     
    int step = 20;      /* step size */
    int celsius;     
    int fahr = upper;

    fprintf(stdout, "Fahrenheit to Celsius conversion\n");
    
    

    while (fahr >= lower ) 
    {         
        celsius = (5.0/ 9.0) * (fahr - 32);
	printf("%d\t%d\n",fahr,  celsius);         
	fahr -= step;
    }   
}
