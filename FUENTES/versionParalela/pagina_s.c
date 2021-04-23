/************************************************************************************
   Fichero: pagina.c (SERIE)

   Se aplica a una pagina en formato PGM el siguiente tratamiento
     -- filtrado para minimizar el rudio
     -- encriptacion
     -- preparacion del proceso para la carga de la pagina en la nube

   Ficheros de entrada:   xx.pgm (pagina en formato pgm)
   Ficheros de salida:	  xx_fil_ser.pgm    pagina filtrada
                          xx_cif_ser.pgm    pagina encriptada

   Compilar el programa junto con filter.c, encript.c y preparar_subida.c

***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "pixmap.h"
#include "filter.h"
#include "encript.h"
#include "preparar_subida.h"


/*************************              MAIN                  **********************/
/***********************************************************************************/

void main(int argc, char **argv)
{
  char name[100];
  int i;

  // Pagina: original, filtrada y cifrada
  pagina page_ori,page_fil,page_cif;

  // calculo de tiempos
  struct timeval t0,t1;
  double tej1,tej2,tej3,tej;

  if (argc != 3)
  {
    printf ("\nUSO: programa pagina limite\n");
    exit (0);
  }

  // Lectura de la pagina de entrada: solo paginas graylevel en formato .pgm
  if (load_pixmap(argv[1], &page_ori) == 0)
  {
    printf ("\nError en lectura del fichero de entrada: %s\n\n",argv[1]);
    exit (0);
  }

  /* Procesado de pagina: generar nuevas paginas (filtrada y encriptada)      */
  /**********************************************************************************************************/
  printf("\n --> Procesando la pagina: %s (%d x %d). Limite: %.1f\n",argv[1],page_ori.h,page_ori.w,atof(argv[2]));

  gettimeofday(&t0, 0);
  generar_pagina_filtrada(&page_ori,&page_fil,atof(argv[2]));
  gettimeofday(&t1, 0);
  tej1 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Filtrar la pagina: \tTej. serie = %1.1f ms", tej1*1000);

  gettimeofday(&t0, 0);
  generar_pagina_encriptada(page_fil,&page_cif);
  gettimeofday(&t1, 0);
  tej2 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Cifrar la pagina: \t\tTej. serie = %1.1f ms", tej2*1000);

  gettimeofday(&t0, 0);
  preparar_subida(page_cif);
  gettimeofday(&t1, 0);
  tej3 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Preparar la subida: \tTej. serie = %1.1f ms", tej3*1000);

  tej = tej1+tej2+tej3;
  printf("\n\n     TOTAL: \t\t\tTej. serie = %1.1f ms\n\n", tej*1000);

  /* Escritura de las paginas en el disco                                         */
  /*********************************************************************************/
  strcpy(name,argv[1]);
  name[strlen(name)-4]='\0';
  strcat(name,"_fil_ser.pgm");
  store_pixmap(name,page_fil);

  strcpy(name,argv[1]);
  name[strlen(name)-4]='\0';
  strcat(name,"_cif_ser.pgm");
  store_pixmap(name,page_cif);

  // Borrar las paginas
  borrar_pagina(page_ori);
  borrar_pagina(page_fil);
  borrar_pagina(page_cif);
}

