/* Fichero: pixmap.h */

#define NEGRO   0
#define BLANCO  255
#define MAX_VAL 256     /* Rango de posibles valores de grises */


typedef struct
{
  int w;                 /* Width */
  int h;                 /* Height */
  unsigned char *dat;    /* Image */
  unsigned char **im;
}pagina;

//Carga la imagen con nombre filename en ipage
//Parametros
	//filename --> Nombre de la imagen
	//ipage --> Puntero de la pagina generada
extern int load_pixmap(char *filename, pagina *ipage);

//Guarda la imagen con nombre filenaeme en opage
//Parametros
	//filename --> Nombre de la imagen
	//opage --> Puntero de la pagina guardada
extern void store_pixmap(char *filename, pagina opage);

//Genra la pagina de opage con la structura pagina
//Parametros
	//opage --> Puntero a la imagen
	//h --> altura de la imagen
	//w --> anchura de la imagen
	//val --> ???
extern void  generar_pagina(pagina *opage, int h, int w, unsigned char val);

//Borra la imagen del puntero ipage
//Parametros
	//ipage --> Puntero que contiene la imagen
extern void  borrar_pagina(pagina ipage);


