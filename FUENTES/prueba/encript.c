/************************************************************************************
     Fichero: encript.c

 	Generar la pagina encriptada

***********************************************************************************/

#include "pixmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



//////////////////////////////////////////////////////////////////////////////////////
/*          codigo para el encriptado de 2 pixeles con el metodo de HILL            */
//////////////////////////////////////////////////////////////////////////////////////
//Parametros
	//v1 --> Primer pixel
	//v2 --> Segundo pixel
void encriptar_pixeles (unsigned char *v1, unsigned char *v2) {

	//DEFINO LA MATRIZ DE ENCRIPTADO
	int matrizEnc [2][2];
	matrizEnc[0][0] = 21;
	matrizEnc[0][1] = 35;
	matrizEnc[1][0] = 18;
	matrizEnc[1][1] = 79;

	//EN LOS MISMOS PUNTEROS QUE RECIBE COMO PARAMETRO, GUARDA LOS PIXELS ENCRIPTADOS
	*v1 = (unsigned char)( matrizEnc[0][0]*(int)(*v1) + matrizEnc[0][1]*(int)(*v2) )%256;
	*v2 = (unsigned char)( matrizEnc[1][0]*(int)(*v1) + matrizEnc[1][1]*(int)(*v2) )%256;

} //END ENCRIPTAR_PIXELES


//////////////////////////////////////////////////////////////////////////////////////
/*      codigo para generar la pagina encriptada ultilizando la pagina filtrada     */
//////////////////////////////////////////////////////////////////////////////////////
//Parametros
	//in_page --> Pagina filtrada
	//out_page --> Pagina encriptada despues del proceso
void generar_pagina_encriptada(pagina in_page, pagina *out_page) {

	generar_pagina(out_page,in_page.h,in_page.w,NEGRO);
	int height, width;
	unsigned char pixel1, pixel2;

	//FOR QUE RECORRA EL ARRAY DE LA IMAGEN PARA ENCRIPTAR DE A DOS PIXELS
	#pragma omp parallel for schedule(runtime) private(width,pixel1,pixel2) collapse(2)
	for (height=0;height<in_page.h;height++) {
		for (width=0;width<in_page.w;width=width+2) {
			pixel1 = in_page.im[height][width];
			pixel2 = in_page.im[height][width+1];

			//encriptar_pixeles (&in_page.dat[width], &in_page.dat[width+1]);
   			encriptar_pixeles(&pixel1, &pixel2);
			out_page->im[height][width] = pixel1;
			out_page->im[height][width+1] = pixel2;
		}
	}
} //END GENERAR_PAGINA_ENCRIPTADA
