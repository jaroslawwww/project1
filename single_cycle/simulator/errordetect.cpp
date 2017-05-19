#include "errordetect.h"
using namespace std;

void errordump(int i)
{
	//FILE* file_ptr;
	//file_ptr = fopen("error_dump.rpt", "w");
	if(i == 1) fprintf( file_ptr , "In cycle %d: Write $0 Error\n", cycle);
	else if(i == 2) fprintf(file_ptr , "In cycle %d: Number Overflow\n", cycle); 
	else if(i == 3)	fprintf(file_ptr , "In cycle %d: Overwrite HI-LO registers\n", cycle); 
	else if(i == 4)	fprintf(file_ptr , "In cycle %d: Address Overflow\n", cycle); 
	else fprintf(file_ptr , "In cycle %d: Misalignment Error\n", cycle);
	//fclose(file_ptr);
}

