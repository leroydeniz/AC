/************************************************************************************
   Fichero: filter.c

   Contiene las funciones para el filtrado de la pagina
***********************************************************************************/
#include <math.h>
#include "pixmap.h"
#include <stdio.h>
#include <omp.h>

#define NUM_IT 100


/* Copia la pagina in_page en la pagina out_page  */
/**************************************************/
//Parametro
	//in_page --> La pagina a copiar
	//out_page --> La copia de in_page

void copiar_pagina(pagina *in_page, pagina *out_page)
{
	int i,j;
	//#pragma omp parallel for schedule(static,0) private(j) collapse(2)
	for (i=0;i<in_page->h;i++)
		for (j=0;j<in_page->w;j++)
      			out_page->im[i][j]=in_page->im[i][j];
}

//Calcula la media de los pixeles de alrededor del pixel im[x][y]
//Parametros
	//in_page--> Pagina de donde se cogeran los pixeles
	//x --> Fila del pixel
	//y --> Columna del pixel

int calcularMatrizFiltro(pagina *in_page, int x, int y)
{
   int result = 0;

   /* este for no amerita paralelizarlo porque solo recoreo 9 elementos */
   for(int i=-1; i<=1; i++) {
      for(int j=-1; j<=1; j++) {
         result += in_page->im[x+i][y+j];
      }
   }
   return result/9;
}

/* Aplicar filtro a una pagina                                  */
/****************************************************************/
//Parametros
	//in_page --> La pagina a filtrar
	//out_page --> La pagina una vez filtrada

double filtrar_pagina(pagina *in_page, pagina *out_page)
{

//////////////////////////////////////////////////////////////////////////
/* POR HACER: aplicar el filtro de suavizado a la pagina in_page       */
/* se aplica a la pagina in_page, dejando el resultado en out_page      */
/* la funcion devuelve dos valores:                                     */
/* el valor medio y minimo de todos los pixeles de la pagina filtrada   */
/* la función devuelve el valor medio menos el mínimo                 */
//////////////////////////////////////////////////////////////////////////
   int i, j, dim = ((in_page->w)-2) * ((in_page->h)-2), minimo = 255;
   double sum = 0.0, media = 0.0, valor = 0.0;

   #pragma omp parallel for schedule(runtime) private(j,valor) reduction(+:sum) reduction(min:minimo)
   for(i=1; i< in_page->h-1; i++) {
      for(j=1; j< in_page->w-1; j++) {
         valor = calcularMatrizFiltro(in_page, i, j);
         out_page->im[i][j] = valor;
         sum += valor;
         if(valor < minimo) {
            minimo = valor;
         }
      }
   }
   return (sum / dim) - minimo;
}

/* Genera la pagina filtrada               */
/*******************************************/
//Parametros
	//in_page --> La pagina original
	//out_page --> La pagina filtrda
	//limite --> Limite de filtrado de la imagen

void generar_pagina_filtrada(pagina *in_page, pagina *out_page, float limite)
{
   generar_pagina(out_page,in_page->h,in_page->w,NEGRO);
   copiar_pagina(in_page,out_page);
   double result=0;
   /* este for no amerita paralelizarlo porque cada pagina depende de que haya terminado la anterior */
   for(int i=0; i<NUM_IT; i++) {
      result = filtrar_pagina(in_page, out_page);
      if(result < limite) {
	printf ("\nFILTRADO: %d iteraciones, limite %.3f\n", i+1, result);
         break;
      }
      copiar_pagina(out_page,in_page);
   }

 /* POR HACER: generar la pagina filtrada a partir de la pagina original */
 /* Proceso iterativo. Condicion final de filtrado:                      */
 /*     (a) superar el numero maximo de iteraciones                      */
 /*     (b) valor medio menos minimo inferior al limite                  */
 /* asegurar que la pagina final queda en out_page                       */
 //////////////////////////////////////////////////////////////////////////
}
