/*
 *	Para este test, tambien agregue estas estructuras al hashADT, simplemente por el hecho de que
 *	generaban problemas de compilacion :S.
*/
#include<stdio.h>
#include"../libs/hashADT.h"
#include"../libs/listADT.h"

typedef struct 							/*Estructuras incluidas aca para poder realizar pruebas.*/
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

int
main(void)
{
	hashADT hashTable = NewHashTable();
	activityADT actividad1, actividad2, actividad3, actAux, actividad4;
	struct activityCDT _actividad1, _actividad2, _actividad3, _actAux, _actividad4;
	actInfo info1, info2, info3, info4;

	actividad1 = &_actividad1;		/*Para no reservarles memoria y bue...*/
	actividad2 = &_actividad2;	
	actividad3 = &_actividad3;
	actividad4 = &_actividad4;
	actAux = &_actAux;

	info1.ID = "A";
	actividad1->info = &info1;
	info2.ID = "B";
	actividad2->info = &info2;
	info3.ID = "C";
	actividad3->info = &info3;
	info4.ID = "D";
	actividad4->info = &info4;

	printf("Prueba para ver si se insertan.\n");
	printf("%s\n",InsertInTable(hashTable, actividad1)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad2)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad3)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad4)?"SI":"NO");

	printf("Prueba para ver si no se insertan, dado que ya estan insertadas.\n");
	printf("%s\n",InsertInTable(hashTable, actividad1)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad2)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad3)?"SI":"NO");
	printf("%s\n",InsertInTable(hashTable, actividad4)?"SI":"NO");


	printf("Prueba para ver si busca bien.\n");
	printf("%s\n", SearchInTable(hashTable, "A")->info->ID);
	printf("%s\n", SearchInTable(hashTable, "B")->info->ID);
	printf("%s\n", SearchInTable(hashTable, "C")->info->ID);
	printf("%s\n", SearchInTable(hashTable, "D")->info->ID);

	printf("Prueba para ver si se borran.\n");
	printf("%s\n",DeleteFromTable(hashTable, "A")?"SI":"NO");
	printf("%s\n",DeleteFromTable(hashTable, "C")?"SI":"NO");
	printf("%s\n",DeleteFromTable(hashTable, "C")?"SI":"NO");
	if((actAux = SearchInTable(hashTable, "A")) == NULL)
		printf("No ta!\n");
	if((actAux = SearchInTable(hashTable, "B")) != NULL)
		printf("%s\n", actAux->info->ID);
	if((actAux = SearchInTable(hashTable, "C")) == NULL)
		printf("No ta!\n");
	if((actAux = SearchInTable(hashTable, "D")) != NULL)
		printf("%s\n", actAux->info->ID);
	
	FreeHashTable(hashTable);
	
	printf(":D\n");

	return 0;
}
