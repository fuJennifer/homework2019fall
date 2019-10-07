#include<stdio.h>
#include<omp.h>
int a[50][50];
int b[50][50];
int  main()
{
#pragma omp parallel
{
#pragma omp sections 
{
  
 //initializing data (phase 1)
  #pragma omp section
  {
 for (int m=0;m<50;m++)
 {
   for (int n=0;n<50;n++)
    {
      a[m][n]=0;
      b[m][n]=m+n;
     // nthreads=omp_get_num_threads();
      int tid= omp_get_thread_num();
      printf("thread id is %d :a[%d][%d] is %d,b[%d][%d]is %d\n",tid,m,n,a[m][n],m,n,b[m][n]);
     }
 }
  }
  #pragma omp section
  {
//2-d matrix transposition (phase 2)
 for (int i = 1; i<= 48; i++)
 {
    for (int j = 1; j <=48; j++)
   {
     a[j][i] = b[i][j];
     int tid=omp_get_thread_num();
    // nthreads=omp_get_num_threads();
     printf("thread id is %d :a[%d][%d] is %d\n",tid,j,i,a[j][i]);
    }
 }
  }
}
}
 return 0;
}
