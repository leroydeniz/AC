/*********************************************************************

  speedup.c

 ******************************************************************/
#include <stdio.h>
#include <sys/time.h>


#define VECES 10
int veces;

// Declaracion de constantes y variables

#define N 10000000

struct timeval 	t0, t1;

int	i;
int	C[N], J[N];


// RUTINAS AUXILIARES

void TrazaTiempo(char * pTexto, struct timeval *pt0, struct timeval *pt1)
{
  double tej;

  tej = (pt1->tv_sec - pt0->tv_sec) + (pt1->tv_usec - pt0->tv_usec) / 1e6;
  printf("%s (serie) = %10.3f ms\n",pTexto,tej*1000);
}


void SacarVector(int *V, int L1, int L2)
{
  int i;

  for (i=L1; i<L2; i++)
  {   
    if(i%5==0) printf("\n"); 
    printf("%d ",V[i]);
  }
  printf("\n");
}


// PROGRAMA PRINCIPAL

main ()  
{

for (veces=0;veces<VECES;veces++)
{
  //Inicializaciones

  for(i=0; i<N; i++)
   {
     C[i] = i;
     J[i] = 6;
   }

  // Comienzo del programa
 
  gettimeofday(&t0, 0);

 for(i=0; i<N; i++)
  { 
    C[i] = ((C[i]+1) / J[i])+1;
    J[i] = (C[i] * J[i] + 1) / C[i] * J[i];
  }
  gettimeofday(&t1, 0);
  TrazaTiempo("Time: ",&t0,&t1);
  
 } //fin del for VECES
  
  // RESULTADOS FINALES: se imprimen los primeros y los ultimos 10 elementos 
  printf("C-> ");
  SacarVector (C, 0, 10);
  SacarVector (C, N-10,N);
  printf("J-> ");
  SacarVector (J, 0, 10);
  SacarVector (J, N-10, N);
}

