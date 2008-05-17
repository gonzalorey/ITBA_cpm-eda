#ifndef DEFENSIVA_H_
#define DEFENSIVA_H_

#include <assert.h>

#define  Precondicion(c)     assert(c)
#define  Postcondicion(c)    assert(c)
 
/* Funcion:					Error
 * Uso:						Error("Memoria insuficiente.\n");
 * ----------------------------------------------------------------------
 * Descripcion:				Muestra en pantalla el error que se genero.
 * 							y sale del programa.
 * ----------------------------------------------------------------------
 * Precondicion:			String correcto.
 * Postcondicion:			Fin del programa y mensaje de error.		
*/
void Error(char * msg);

#endif /*DEFENSIVA_H_*/
