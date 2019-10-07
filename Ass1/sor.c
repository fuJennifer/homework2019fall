#include<stdio.h>
#include<omp.h>
int a[50][50];
int  main()
{
 //initializing data (phase 1)
 for (int m=0;m<50;m++)
   for (int n=0;n<50;n++)
       a[m][n]=m+n;
 //sor processing (phase 2)
  // int iam;
  #pragma omp parallel
 { 
 for (int i = 1; i<= 48; i++)
 {
   // iam=omp_get_thread_num();
    //printf("tid is %d\n",iam);
    for (int j = 1; j <=48; j++)
     {
       for (int k = 1; k <=48; k++)
        {
	  //np= omp_get_num_threads();
	 int iam= omp_get_thread_num();
          a[j][k] = 2 * (a[j][k] + a[j + 1][k] + a[j - 1][k] + a[j][k + 1] + a[j][k - 1]);
	  printf("tid is %d a[%d][%d]=%d\n",iam,j,k,a[j][k]);
        }
      }
   }
 }
 return 0;
}
