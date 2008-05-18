/*
 *	Para este test, tambien agregue estas estructuras al listADT, simplemente por el hecho de que
 *	generaban problemas de compilacion :S.
*/
#include<stdio.h>
#include"../libs/listADT.h"

typedef struct 				/*Incluida aca solo para este test.*/
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
	listADT list = NewList();
	listADT aux;
	activityADT actividad1, actividad2, actividad3, actAux, actividad4;
	struct activityCDT _actividad1, _actividad2, _actividad3, _actAux, _actividad4;

	actividad1 = &_actividad1;		/*Para no reservarles memoria y bue...*/
	actividad2 = &_actividad2;	
	actividad3 = &_actividad3;
	actividad4 = &_actividad4;
	actAux = &_actAux;

	actInfo info1, info2, info3, info4;
	info1.ID = "A";
	actividad1->info = &info1;
	info2.ID = "B";
	actividad2->info = &info2;
	info3.ID = "C";
	actividad3->info = &info3;
	info4.ID = "D";
	actividad4->info = &info4;

	Insert(&list, actividad1);
	Insert(&list, actividad4);
	Insert(&list, actividad2);
	Insert(&list, actividad3);

	printf("%s\n",ElementBelongs(list, "A")?"SI":"NO");
	printf("%s\n",ElementBelongs(list, "D")?"SI":"NO");
	printf("%s\n",ElementBelongs(list, "B")?"SI":"NO");
	printf("%s\n",ElementBelongs(list, "C")?"SI":"NO");
	
	printf("\nPrueba para ver que inserto y en que orden.\n");
	aux = list;
	while(!ListIsEmpty(aux))
	{
		actAux = ListHead(aux);
		aux = ListTail(aux);
		printf("%s\n", actAux->info->ID);
	}

	Delete(&list, "B");
	aux = list;
	printf("\nPrueba para ver si borro.\n");
	while(!ListIsEmpty(aux))
	{
		actAux = ListHead(aux);
		aux = ListTail(aux);
		printf("%s\n", actAux->info->ID);
	}
	printf("B %s está.\n",ElementBelongs(list, "B")?"SI":"NO");

	Insert(&list, actividad2);
	Insert(&list, actividad4);
	printf("\nPrueba para ver que inserto y en que orden 2.\n");
	aux = list;
	while(!ListIsEmpty(aux))
	{
		actAux = ListHead(aux);
		aux = ListTail(aux);
		printf("%s\n", actAux->info->ID);
	}

	FreeList(&list);
	
	printf(":D\n");

	return 0;
}
