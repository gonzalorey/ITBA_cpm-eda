/*
 * Lista lineal ordenada sin header y sin repeticiones.
 */

#ifndef listActADT_H_
#define listActADT_H_

#include "../libs/graphADT.h"

typedef struct listActCDT * listActADT;	

/* Funcion:					NewActList
 * Uso:						list = NewActList();
 * ------------------------------------------------------------------------
 * Descripcion:				Inicializa la lista.
 * 							Usarla una sola vez antes de empezar a 
 * 							usar el resto de las operaciones.
 * 							No hay error posible.
 * ------------------------------------------------------------------------
 * Precondicion:			-
 * Postcondicion:			Lista creada
 */ 
listActADT NewActList(void);

/* Funcion:					InsertAct
 * Uso:						InsertAct(&list, act);
 * ------------------------------------------------------------------------
 * Descripcion:				InsertActa una actividad en la lista ordenada.
 * 							Si la misma ya existia, retorna 0, caso
 * 							contrario, devuelve un 1.
 * 							Si hay problemas en la alocacion de memoria,
 * 							finaliza la aplicacion.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			Lista con la nueva actividad, si no es que
 * 							ya estaba dentro.
 */
int InsertAct(listActADT * list, activityADT act);

/* Funcion:					DeleteAct
 * Uso:						DeleteAct(&list, "A");
 * ------------------------------------------------------------------------
 * Descripcion:				Elimina la actividad de la lista ordenada que
 * 							se corresponde con el ID recibido.
 * 							Si la misma no existia, devuelve 0, caso
 * 							contrario, devuelve 1.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			Lista sin la actividad.
 */
int DeleteAct(listActADT * list, char * ID);

/* Funcion:					ListActIsEmpty
 * Uso:						if(ListActIsEmpty(list))
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Devuelve 1 si la lista esta vacia, y 0 en 
 * 							caso contrario. 
 * ------------------------------------------------------------------------
 * Precondicion:			Lista que sea valida, previamente creada.
 * Postcondicion:			-	
 */
int ListActIsEmpty(listActADT list);

/* Funcion:					ElementActBelongs
 * Uso:						if((act = ElementActBelongs(list, "A")) == NULL)	
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Si hay una actividad cuyo ID corresponda con 
 * 							el recibido, retorna tal actividad, caso
 * 							contrario, retorna NULL. 
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Postcondicion:			-
 */
activityADT ElementActBelongs(listActADT list, char * ID);

/* Funcion:					ListActHead
 * Uso:						if(act < ListActHead(list))
 * 							...
 * ------------------------------------------------------------------------
 * Descripcion:				Es de consulta. Devuelve la primera componente
 * 							de la lista, sin eliminarla.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida, no vacia.
 * Postcondicion:			-
 */
activityADT ListActHead(listActADT list);

/* Funcion:					ListActTail
 * Uso:						while(act != ListActHead(list))
 * 								list = ListActTail(list);
 * ------------------------------------------------------------------------
 * Descripcion:				Es de consulta. Devuelve la sublista que 
 * 							corresponde a la lista original. No altera la
 * 							lista. Se usa conjuntamente con ListActHead para
 * 							iterar sobre las componentes de la lista.
 * ------------------------------------------------------------------------
 * Precondicion:			Lista valida, no vacia.
 * Postcondicion:			-
 */
listActADT ListActTail(listActADT list);

/* Funcion:					FreeActList
 * Uso:						FreeActList(&list);
 * -------------------------------------------------------------------------
 * Descripcion:				Destruye la lista, liberando la memoria alocada
 * 							para la creacion y uso de la misma.
 * -------------------------------------------------------------------------
 * Precondicion:			Lista valida.
 * Poscondicion:			-
 */
void FreeActList(listActADT * list);

#endif /*listActADT_H_*/
