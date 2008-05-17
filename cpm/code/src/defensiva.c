#include <stdio.h>
#include "../libs/defensiva.h"

void
Error(char * msg)
{
	fprintf(stdout, msg);
	exit(EXIT_FAILURE);	
}