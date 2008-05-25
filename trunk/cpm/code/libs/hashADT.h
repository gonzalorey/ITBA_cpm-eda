#ifndef HASHADT_H_
#define HASHADT_H_

typedef struct activityCDT * activityADT; 

typedef struct stageCDT * stageADT;

typedef struct hashCDT * hashADT;

/* Funcion:					NewHashTable
 * Uso:						NewHashTable();
 * ----------------------------------------------------------------------
 * Descripcion:				Crea una nueva tabla de hash. Sale del
 * 							programa en caso de error.
 * ----------------------------------------------------------------------
 * Precondicion:			-
 * Postcondicion:			Tabla creada.
 */
hashADT NewHashTable(void);

/* Funcion:					FreeHashTable
 * Uso:						FreeHashTable(table);
 * ----------------------------------------------------------------------
 * Descripcion:				Libera la memoria reservada para la creacion
 * 							y uso de la tabla.
 * ----------------------------------------------------------------------
 * Precondicion:			Tabla previamente creada.
 * Postcondicion:			-
 */
void FreeHashTable(hashADT hashTable);

/* Funcion:					InsertInTable
 * Uso:						InsertInTable(table, activity);
 * ----------------------------------------------------------------------
 * Descripcion:				Inserta la actividad dentro de la tabla,
 * 							hasheandola en base a la ID de la misma.
 * 							Retorna 0 en caso de que la actividad
 * 							a insertar ya estuviera en la tabla, y 
 * 							1 en caso contrario.
 * ----------------------------------------------------------------------
 * Precondicion:			Tabla previamente creada. Actividad valida.
 * Postcondicion:			Actividad insertada en la tabla.
 */
int InsertInTable(hashADT hashTable, activityADT act);

/* Funcion:					DeleteFromTable
 * Uso:						DeleteFromTable(table, "A");
 * ----------------------------------------------------------------------
 * Descripcion:				Borra la actividad de la tabla que se 
 * 							corresponde con el ID recibido. En caso de 
 * 							que la misma no estuviera dentro de la 
 * 							tabla, retorna 0, caso contrario, 1.
 * ----------------------------------------------------------------------
 * Precondicion:			Tabla previamente creada. String no nulo.
 * Postcondicion:			Actividad borrada de la tabla.
 */
int DeleteFromTable(hashADT hashTable, char * ID);

/* Funcion:					SearchInTable
 * Uso:						SearchInTable(table, activity);
 * ----------------------------------------------------------------------
 * Descripcion:				Busca una actividad dentro de la tabla que
 * 							se corresponda con el ID recibido, en
 * 							caso de encontrarla, la retorna en su nombre,
 * 							sino, retorna NULL.
 * ----------------------------------------------------------------------
 * Precondicion:			Tabla previamente creada. Actividad valida.
 * Postcondicion:			Actividad retornada.
 */
activityADT SearchInTable(hashADT hashTable, char * ID);

#endif /*HASHADT_H_*/
