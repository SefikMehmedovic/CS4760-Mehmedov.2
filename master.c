
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
	int input;

	while ((input = getopt (argc, argv, "hn:s:")) != -1)
	
	{
	 switch(input)
	 {
		case 'h':
		printf("To run the program use ./master -n x to indicate the max total of child process to fork off\n");
		printf("another option is -s to indicate how many children should run at the same time\n ");
		printf("Example: ./master -n 4 -s 10\n ");
		break;
		
		case 'n':
		printf("case n\n");
		break;
		
		case 's':
		printf(" case s ");
		break;
	 }
	
	}
	return 0;
}

