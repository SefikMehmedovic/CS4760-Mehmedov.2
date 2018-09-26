
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void memoryExample();

// not sure what it does or what 323800 is but a alot easier than creating one using ftok
// seen it on the example so...
#define SHMKEY 323800
#define BUFF_SZ	sizeof ( int )

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

  switch ( fork())
  {
    case -1:
        printf("failed to fork\n");
        return (1);
    case 0:
      execlp("./worker");
      printf("worker failed\n");
      break;
    default:
        memoryExample();
        break;
  }

  // void memoryExample();
   
   
	return 0;
}

void memoryExample()
{
  // get shared memory segment ID.. not 100% of this either 
   int shmid = shmget (SHMKEY, BUFF_SZ, 0711 | IPC_CREAT );
   if (shmid == -1)
   {
     printf("Parent: Error in shmget \n");
     exit(1);
   }
   // not sure what 0,0 is for 
   char * paddr = ( char * ) (shmat (shmid, 0, 0) );
   int * pint = (int *) (paddr);
   printf("Master: Written Val: = ", *pint, "\n");
  /* for ( int i = 0; i<10; i++)
   {
     sleep(1);
     *pint = 10*i;
     printf("Master: Written Val: = \n", *pint, "\n");
   }*/
}
