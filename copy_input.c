#include <stdio.h>

main()
{
	int c;
	while( (c = getchar()) != EOF)
	{
		if(c == ' ')
		{
		  while ( c  == ' ' )
		  {
                     c = getchar();
		  }
		  putchar(' ');	
		}
			
	        putchar(c);
	       
	}
}
