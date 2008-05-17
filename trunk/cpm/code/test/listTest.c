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
	activityADT actividad1, actividad2, actividad3, actAux;
	actInfo info1, info2, info3;
	info1.ID = "A";
	actividad1->info = &info1;
	info2.ID = "B";
	actividad2->info = &info2;
	info3.ID = "C";
	actividad3->info = &info3;

	Insert(&list, actividad1);
	Insert(&list, actividad2);
	Insert(&list, actividad3);

	ElementBelongs(list, actividad2);
	
	aux = list;
	while(!ListIsEmpty(aux))
	{
		actAux = ListHead(aux);
		aux = ListTail(aux);
		printf("%s\n", actAux->info->ID);
	}

	Delete(&list, actividad2);
	printf("%s\n",ElementBelongs(list, actividad2)?"SI":"NO");

	FreeList(&list);
	
	printf(":D\n");

	return 0;
}
