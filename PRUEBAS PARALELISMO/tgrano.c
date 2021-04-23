/*********************************************************************
  tgrano.c (SERIE)

  Ejemplo para ver el efecto del tamaino de las tareas
  (grano) en el tiempo de ejecucion  
**********************************************************************/

#include <stdio.h>
#include <sys/time.h>

#define N 10000000		// tamaino maximo del vector

int A[N];

main () 
{
  struct timeval t0, t1;
  double tej;

  int  i, tam_vec;

  printf("\n Tamaino del vector a procesar --->  ");
  scanf("%d", &tam_vec);

 // #pragma omp parallel for private (i)
  for (i=0; i<tam_vec; i++) A[i] = 1;

  gettimeofday(&t0, 0);

  for (i=0; i<tam_vec; i++)
  {
    int j;

    for (j=1; j<=1000; j++)
      A[i] = (A[i]*A[i] + 1) * (A[i]*A[i] - 1) + (j%2);
  }

  gettimeofday(&t1, 0);


  tej = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n\n Tej. (serie) = %1.3f ms\n\n", tej*1000);
}
