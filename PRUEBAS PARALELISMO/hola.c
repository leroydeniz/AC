/**********************************************************************************
    hola.c (OPENMP)
    Generacion de varios threads y modificacion del numero de threads mediante:
          export OMP_NUM_THREADS=4          
**********************************************************************************/
#include <stdio.h>
#include <omp.h>

#define N  24 
int A[N];

main  ()
{
  int i, tid, nthr;
  for (i=0; i<N; i++) A[i]=0;

  #pragma omp parallel private(tid, nthr)
  {  
    nthr = omp_get_num_threads();
    tid = omp_get_thread_num();
    printf ("Thread %d de %d en marcha \n", tid, nthr);   
    A[tid] = tid + 10;
    printf ("El thread %d ha terminado \n", tid);
  }

  for (i=1; i<=N; i++)
  {
   printf (" A(%2d)=%3d ", i-1, A[i-1]);
   if (!(i%8)) printf("\n");
  }
}

