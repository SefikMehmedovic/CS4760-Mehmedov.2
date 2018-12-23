#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void child();

#define SHMKEY 321800
#define BUFF_SZ	sizeof ( int )


int main() {
    //printf("CCHILLLD\n");
    
child();
   
return 0;
}

void child() {


int getValue;	

  int shmid = shmget (SHMKEY,BUFF_SZ , 0711 | IPC_CREAT );
  if (shmid == -1)
   {
    printf("Worker: Error in shmget..\n");
    return 1;
   }
  int *cint = ( shmat (shmid, NULL, 0) );
 
  getValue = cint[0];
  for (int i= 0; i < (cint[0] * 1000000); i++)
  {
    cint[2]++;
    if(cint[2] > 999)
    {
      cint[1]++;
      cint[2] = 0;
    }
  }
  shmdt(cint);
  
  /* old code from example
  printf("Worker: Read Val: =  ", *cint, "\n");
  for ( int i =0; i<10; i++)
  {
    sleep(1);
    printf("Worker: Read Val: =  ", *cint, "\n");
  }*/
}


