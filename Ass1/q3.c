#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mainCV=PTHREAD_COND_INITIALIZER;
pthread_cond_t workerCV=PTHREAD_COND_INITIALIZER;
int varCon=0;

void * printNormal()
{
 //pthread_mutex_lock(&lock);
 for(int i=1;i<=20;i++)
 {
   varCon=i;
   if(i%5==0)
    {
       pthread_mutex_lock(&lock);
       pthread_cond_signal(&workerCV);
       pthread_cond_wait(&mainCV,&lock);
       pthread_mutex_unlock(&lock);
       
    }
   else
   {
       printf("thread id is %ld:%d\n",pthread_self(),i);
       sleep(1);
   }
       
 }
 pthread_exit(NULL);
}
void * printSpecial()
{//printf("here");
 while(1)
 {
 pthread_mutex_lock(&lock);
 //printf("here");
 pthread_cond_wait(&workerCV,&lock);
 printf("thread id is %ld:%d\n",pthread_self(),varCon);
 sleep(1);
 pthread_cond_signal(&mainCV);
 //pthread_cond_wait(&workerCV,&lock);
 pthread_mutex_unlock(&lock);
 }
 
}
int main()
{
   pthread_t thread1, thread2;
   pthread_create(&thread1,NULL,&printNormal,NULL);
   pthread_create(&thread2,NULL,&printSpecial,NULL);
   pthread_join(thread1,NULL);
   pthread_join(thread2,NULL);
   return 0;
}

