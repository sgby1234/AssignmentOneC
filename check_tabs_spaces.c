#include <stdio.h>

main()
{
	int nLines = 0;
	int nTabs = 0;
	int nSpaces = 0;
	int c;

	while((c = getchar()) != EOF)
	{
		if(c == ' ')
			nSpaces++;
		else if(c == '\n')
			nLines++;
		else if(c == '\t')
			nTabs++;
	}
	

	fprintf(stdout,"Number of Lines = %d\nNumber of Tabs = %d\nNumber of Spaces = %d", nLines, nTabs, nSpaces);
}
