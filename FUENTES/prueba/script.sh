#!/bin/sh
#BUCLE PARA RECORRER LAS TRES IMAGENES
for imagen in Libro1.pgm Libro2.pgm Libro3.pgm
do
        #!BUCLE PARA VARIAR LA PLANIFICACION
        for plan in static dynamic
        do
                #BUCLE PARA VARIAR EL NUMERO DE INSTRUCCIONES
                for bloque in 0 1 2 4 8 16 32
                do

                        export OMP_SCHEDULE="$plan,$bloque"

                        #BUCLE PARA VARIAR EL NUMERO DE HILOS
                        for hilos in 2 4 8 16 24 32
                        do
                                echo
                                echo "******************************** ($plan, $bloque) con $hilos hilos en $imagen ********************************"

                                export OMP_NUM_THREADS=$hilos
                                echo

                                if [ $imagen = "Libro1.pgm" ]; then
                                ./app "$imagen" 177
                                ./app "$imagen" 177
                                ./app "$imagen" 177
                                fi
                                if [ $imagen = "Libro2.pgm" ]; then
                                ./app "$imagen" 177.5
                                ./app "$imagen" 177.5
                                ./app "$imagen" 177.5
                                fi
                                if [ $imagen = "Libro3.pgm" ]; then
                                ./app "$imagen" 125
                                ./app "$imagen" 125
                                ./app "$imagen" 125
                                fi
                                echo
                        done
                done
        done
done
