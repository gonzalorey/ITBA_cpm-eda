/*
 * Lista lineal ordenada sin header y sin repeticiones.
 */

#ifndef LISTADT_H_
#define LISTADT_H_

#include "hashADT.h"			/*Como necesitaba definir el tipo de elemento, inclui esa lib.*/

typedef struct listCDT * listADT;	

/* Funcion:					NewList
 * Uso:						list = NewList();
 * ------------------------------------------------------------------------
 * Descripcion:				Inicializa la lista.
 * 							Usarla una sola vez antes de empezar a 
 * 							usar el resto de las operaciones.
 * 							No hay error posible.
 * ------------------------------------------------------------------------
 * Precondicion:			-
 * Postcondicion:			Lista creada
*/ 
listADT NewList(void);

/* Funcion:					Insert
 * Uso:						Insert(&list, act);
 * ------------------------------------------------------------------------
 * Descripcion:				Inserta una actividad en la lista ordenada.
 * 							Si la misma ya existia, retorna 0, caso
 * 							contrario, devuelve un 1.
 * 							Si hay problemas en la alocacion de memoria,
 * 							finaliza la aplicacion.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			Lista con la nueva actividad, si no es que
 * 							ya estaba dentro.
*/
int Insert(listADT * list, activityADT act);

/* Funcion:					Delete
 * Uso:						Delete(&list, "A");
 * ------------------------------------------------------------------------
 * Descripcion:				Elimina la actividad de la lista ordenada que
 * 							se corresponde con el ID recibido.
 * 							Si la misma no existia, devuelve 0, caso
 * 							contrario, devuelve 1.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			Lista sin la actividad.
*/
int Delete(listADT * list, char * ID);

/* Funcion:					ListIsEmpty
 * Uso:						if(ListIsEmpty(list))
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Devuelve 1 si la lista esta vacia, y 0 en 
 * 							caso contrario. 
 * ------------------------------------------------------------------------
 * Precondicion:			Lista que sea valida, previamente creada.
 * Postcondicion:			-	
*/
int ListIsEmpty(listADT list);

/* Funcion:					ElementBelongs
 * Uso:						if((act = ElementBelongs(list, "A")) == NULL)	
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Si hay una actividad cuyo ID corresponda con 
 * 							el recibido, retorna tal actividad, caso
 * 							contrario, retorna NULL. 
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			-
*/
activityADT ElementBelongs(listADT list, char * ID);

/* Funcion:					ListHead
 * Uso:						if(act < ListHead(list))
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Es de consulta. Devuelve la primera componente
 * 							de la lista, sin eliminarla.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida, no vacia.
 * Postcondicion:			-
*/
activityADT ListHead(listADT list);

/* Funcion:					ListTail
 * Uso:						while(act != ListHead(list))
 * 								list = ListTail(list);
 * ------------------------------------------------------------------------
 * Descripcion:				Es de consulta. Devuelve la sublista que 
 * 							corresponde a la lista original. No altera la
 * 							lista. Se usa conjuntamente con ListHead para
 * 							iterar sobre las componentes de la lista.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida, no vacia.
 * Postcondicion:			-
*/
listADT ListTail(listADT list);

/* Funcion:					FreeList
 * Uso:						FreeList(&list);
 * -------------------------------------------------------------------------
 * Descripcion:				Destruye la lista, liberando la memoria alocada
 * 							para la creacion y uso de la misma.
 * -------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Poscondicion:			-
*/
void FreeList(listADT * list);

#endif /*LISTADT_H_*/
