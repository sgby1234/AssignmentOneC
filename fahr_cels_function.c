#include <stdio.h>
float toCelsius(float fahr);
main()
{
	float fahr;
	int step = 20;
	int upper = 300;

	fprintf(stdout, "Fahrenheit  Celsius\n");
	for(fahr = 0; fahr < upper; fahr += step)
	{
		fprintf(stdout, "%.2f\t\t%.2f\n", fahr, toCelsius(fahr));
	}
} 

float toCelsius(float fahr)
{
	return ((5.0/ 9.0) * (fahr - 32));
}
