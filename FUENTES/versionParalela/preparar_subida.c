/************************************************************************************
     Fichero: preparar_subida.c

       Contiene las funciones para preparar la subida de la pagina a la nube
***********************************************************************************/

#include "pixmap.h"
#include "upload.h"
#include <omp.h>

/* Prepara la subida de la pagina encriptada a la nube                         */
/***********************************************************************************/
//Parametros
	//in_page --> La pagina encriptada
void preparar_subida(pagina in_page)
{
	int i,j;
	#pragma omp parallel for schedule(runtime) private (j) collapse(2)
	for(i=0; i<in_page.h; i++) {
	   for(j=0; j<in_page.w; j++) {
		upload(in_page.im[i][j], i, j, in_page.h, in_page.w);
	   }
	}
//////////////////////////////////////////////////////////////////////////////////////
/* POR HACER: codigo para preparar la transmision de la pagina                      */
/* codigo para preparar la subida de la pagina                                      */
/* tened en cuenta la cabecera de la funcion upload (upload.h)                      */
//                                                                                  //
/* extern void upload (unsigned char vp1, int i, int j, int h, int w);              */
/* pixel de la pagina, su posicion (i,j) y dimensiones de la pagina (h,w)           */
/* se trata de aplicar la funcion upload a cada pixel                               */
//////////////////////////////////////////////////////////////////////////////////////

/*
	generar_pagina(out_page,in_page.h,in_page.w,NEGRO);
	copiar_pagina(in_page,out_page);
*/

}

