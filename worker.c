#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void child();

#define SHMKEY 323800
#define BUFF_SZ	sizeof ( int )
#define MILLION 1000000

int main() {
   child();
   
return 0;
}

void child() {
int passedNValue;	
  int shmid = shmget (SHMKEY, BUFF_SZ, 0711);
  
  if (shmid == -1) {
    printf("Worker: Error in shmget..\n");
    exit(1);
    
  }
  int * cint = (int *) (shmat (shmid, 0, 0) );
  passedNValue = cint[0];
  int test = MILLION * passedNValue;
  printf("million: %d \n", test);
  
  /* old code from example
  printf("Worker: Read Val: =  ", *cint, "\n");
  for ( int i =0; i<10; i++)
  {
    sleep(1);
    printf("Worker: Read Val: =  ", *cint, "\n");
  }*/
}


