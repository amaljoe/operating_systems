#include<stdio.h>
#include<semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include <fcntl.h> 
#include <sys/mman.h>
#include<sys/stat.h>
struct data{
  int a[5];
  sem_t full,empty,mutex;
}*d;
int main(){
  int x,index=0,item,i,n,size;
  int fd=shm_open("/shared",O_CREAT|O_RDWR,0777);
  ftruncate(fd,sizeof(struct data));
  d=mmap(NULL,sizeof(struct data),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
  sem_init(&(d->mutex),10,1);
  sem_init(&(d->full),10,0);
  sem_init(&(d->empty),10,5);
  
  
  printf("Enter number of processes:");
  scanf("%d",&n);
  for(i=0;i<n;i++){
    sem_getvalue(&(d->full),&x);
    
    if(x==5)
      {
        printf("Buffer full\n");
        exit(0);
      }
    else
      printf("\nEnter an item to be produced:");
      scanf("%d",&item);
      sem_wait(&(d->mutex));
      sem_wait(&(d->empty));
      d->a[index] = item;
     index=(index+1)%5;
      sem_post(&(d->mutex));
      sem_post(&(d->full));
  }

  
}