#include <stdio.h>

/* print Fahrenheit-Celsius table       
 * for fahr = 0, 20, ..., 300 */   

main()   
{     
    int lower = 0;      /* lower limit of temperature scale */     
    int upper = 300;    /* upper limit */     
    int step = 20;      /* step size */
    int fahr = lower;     





     fprintf(stdout, "Fahrenheit to Celsius conversion\n");
     fprintf(stdout, "Fahr\t Cels\n"); 
     int celsius;     
 
     while (fahr <= upper) 
     {         
        celsius = 5 * (fahr-32) / 9;         
	printf("%d\t%d\n", fahr, celsius);         
	fahr += step;     
     }   
}
