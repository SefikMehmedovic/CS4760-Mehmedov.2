#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sharedMemory(int n, int s);

// not sure what it does or what 323800 is but a alot easier than creating one using ftok
// seen it on the example so...
#define SHMKEY 323800
#define BUFF_SZ	sizeof ( int )

int main(int argc, char* argv[]) {
	int input, n, s; // n total forks, s total forks allowed to exist at one time
  
  bool callFork = false;

	while ((input = getopt (argc, argv, "hn:s:")) != -1)
	
	{
	 switch(input)
	 {
		case 'h':
		printf("To run the program use ./master -n x to indicate the max total of child process to fork off\n");
		printf("another option is -s to indicate how many children should run at the same time\n ");
		printf("Example: ./master -n 10 -s 2 \n ");
		break;
		
		case 'n':
     n = atoi(optarg);
     callFork = true;
	   //printf("case n: %d\n", n);
		  break;
		
		case 's':
     s = atoi(optarg);
		//printf(" case s %d ", s);
     	break;
      
    default:
      //exit program incorrect options
      exit(1);
	
	 }
	
	}
  
 // alarm(2);
  
  if(callFork == true)
  {
    sharedMemory(n,s);
  }
  
  
  /* old code... doesnt work... 
  
  switch ( fork())
  {
    case -1:
        printf("failed to fork\n");
        return (1);
    case 0:
      execlp("./worker"," worker", NULL);
      printf("worker failed\n");
      break;
    default:
        sharedMemory();
        break;
  } */

 return 0;
}

void sharedMemory(int n, int s)
{
    int count = 0;
    
  // get shared memory segment ID.. not 100% of this 
   int shmid = shmget (SHMKEY, BUFF_SZ, 0711 | IPC_CREAT );
   if (shmid == -1)
   {
     printf("Parent: Error in shmget \n");
     exit(1);
   }
   
   char * paddr = ( char * ) (shmat (shmid, 0, 0) );
   int * pint = (int *) (paddr);
   
   pint[0] = 0;
   pint[1] = 0;
   pint[2] = n;
   
   if(n >= s) 
   {
     for (int i = 0; i< s; i++)
     {
       if(fork() == 0)
       {
         execlp("./worker"," worker", NULL);
       }
       else if( fork() == -1)
       {
         printf("failed to fork\n");
         return (1);
       }
     }
     
     while(count < n) 
     {
       wait(NULL);
       if(fork() == 0)
       {
          execlp("./worker"," worker", NULL);
          count++;
       }
        else if( fork() == -1)
       {
         printf("failed to fork\n");
         return (1);
       }
     }
     
   }
   else
   {
     for(int i = 0;i < n; i++)
     {
       if(fork() == 0)
       {
          execlp("./worker"," worker", NULL);
          i++;
       }
        else if( fork() == -1)
       {
         printf("failed to fork\n");
         return (1);
       }
     }
     
     wait(NULL);
     
     printf("Seconds: %d Milliseconds: %d \n",pint[0], pint[1]);
     shmdt(pint);
   }
   
   //example code
  /* printf("Master: Written Val: = ", *pint, "\n");
   for ( int i = 0; i<10; i++)
   {
     sleep(1);
     *pint = 10*i;
     printf("Master: Written Val: = \n", *pint, "\n");
   }*/
}
