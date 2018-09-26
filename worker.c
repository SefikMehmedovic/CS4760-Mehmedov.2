
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void child();

#define SHMKEY 323800
#define BUFF_SZ	sizeof ( int )

int main(int argc, char* argv[]) {
  	
   
   
return 0;
}

void sleep() {
  sleep(1);
  int shmid = shmget (SHMKEY, BUFF_SZ, 0777);
  
  if (shmid == -1) {
    printf("Worker: Error in shmget..\n");
    exit(1);
    
  }
  
  int * cint = (int *) (shmat (shmid, 0, 0) );
  
  for ( int i =0; i<10; i++)
  {
    sleep(1);
    printf("Worker: Read Val: =  ", *cint, "\n");
  }
}


