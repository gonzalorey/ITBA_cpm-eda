#include<stdio.h>
#include<stdlib.h>
#include"../libs/hashADT.h"
#include"../libs/listADT.h"

#define BUCKETSNUMBER 101

/*
typedef struct 							Estructuras incluidas aca para poder realizar pruebas.
{
	char * descrip;
	int duracion;
	char * ID;
	char ** precedentes;
}actInfo;

struct activityCDT
{
	actInfo * info;
	stageADT dest;
	stageADT orig;
	int tag, li, lt,ci, ct;
};

struct stageCDT
{
	int tag;
	int etapaID;
	listADT finalizan;
	listADT comienzan;
	stageADT next;
};
*/

struct hashCDT
{
	listADT table[BUCKETSNUMBER];
	int quant;							/*Cantidad de buckets ocupados en la tabla.*/			
};

hashADT 
NewHashTable(void)
{
	return calloc(1, sizeof(struct hashCDT));
}

void 
FreeHashTable(hashADT hashTable)
{
	int i;
	for(i = 0; i < hashTable->quant; i++)
	{
			if(!ListIsEmpty(hashTable->table[i]))
				FreeList(&(hashTable->table[i]));
	}
	free(hashTable);
}
/*
 * Funcion que genera una clave para la actividad basado en su ID. 
*/ 
static unsigned int
hash(char * actID)
{
	unsigned int key = 0;
	while(*actID)
		key = (key << 5) + *actID++;
	return (key % BUCKETSNUMBER);	
}

int 
InsertInTable(hashADT hashTable, activityADT act)
{
	int key = hash(act->info->ID);
	int rta;
	if(ListIsEmpty(hashTable->table[key]))					/*Lo inserto de esta manera para que	*/
		hashTable->table[key] = NewList();					/*quede claro que se hace un NewList	*/
	if ((rta = Insert(&(hashTable->table[key]),act)) == 1)	/*y para contar cuantos hay.			*/
		hashTable->quant++;
	return rta;
}

int 
DeleteFromTable(hashADT hashTable, char * ID)
{
	int key = hash(ID);
	int rta;
	/*Si la lista se vacia, decremento la cantidad de buckets con elementos.*/
	if((rta = Delete(&(hashTable->table[key]), ID)) == 1 && ListIsEmpty(hashTable->table[key]))
		hashTable->quant--;									
	return rta;
}

activityADT 
SearchInTable(hashADT hashTable, char * ID)
{
	int key = hash(ID);
	if(ListIsEmpty(hashTable->table[key]))
		return NULL;
	return ElementBelongs(hashTable->table[key], ID);
}
