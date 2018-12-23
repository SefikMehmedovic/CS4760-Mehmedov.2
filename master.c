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

//void signalHandler(int sig);
void sharedMemory(int n, int s);

// not sure what it does or what 323800 is but a alot easier than creating one using ftok
// seen it on the example so...

#define SHMKEY 321800
#define BUFF_SZ	sizeof ( int )


int main(int argc, char* argv[]) {

	int input, n, s; // n total forks, s total forks allowed to exist at one time

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
         
	  // printf("case n: %d\n", n);
         break;
		
		case 's':
         s = atoi(optarg);
        // printf("case s: %d\n", s);
     	   break;
    
    case '?':
         fprintf(stderr, "Unknown option %c\n", optopt);
    
    default:
      //exit program incorrect options
     // exit(1);
     return 1;
	
	 }
	
	}
  
 if (n > 20)
 {
   printf("Exceeded n > 20. N is set back to 20---\n");
   n = 20;
 }
 //kill process
  signal(SIGKILL,alarm);
 
  sharedMemory(n,s);
  

  
 
 return 0;
}

void sharedMemory(int n, int s)
{

  //  printf("sharedmemory: \n");
    int count = 0;
  // get shared memory segment ID.. not 100% of this 
   int shmid = shmget (SHMKEY,BUFF_SZ , 0711 | IPC_CREAT );
   if (shmid == -1)
   {
     printf("Parent: Error in shmget \n");
     exit(1);
   }
   
   char * paddr = ( char * ) (shmat (shmid, NULL, 0) );
   int * pint = (int *) (paddr);
   
   pint[0] = n;
   pint[1] = 0;
   pint[2] = 0;

   if(n >= s) 
   {
     for (int i = 0; i < s; i++)
     {
      
       if( fork() == 0)
       {
         execl("./worker"," worker", NULL);
       }
     }
     while(count < n) 
     {
       //wait for child
       wait(NULL);
       count++;
       if((fork()) == 0)
       {
           
           execl("./worker"," worker", NULL);
          
       }
     } 
   }
   else //if s>n 
   {
     for(int i = 0;i < n; i++)
     {
       if(fork() == 0)
       {
          execl("./worker"," worker", NULL);
       }
     }
   }
     //wait for child and print seconds and milliseconds
     wait(NULL);
     printf("Seconds: %d Milliseconds: %d \n",pint[1], pint[2]);
     shmdt(pint);
   
   //example code
  /* printf("Master: Written Val: = ", *pint, "\n");
   for ( int i = 0; i<10; i++)
   {
     sleep(1);
     *pint = 10*i;
     printf("Master: Written Val: = \n", *pint, "\n");
   }*/
}

//void signalHandler(int sig)
//{
//  printf("Caught signal %d\n",sig);
//  //kill (pid,SIGINT);
//}
