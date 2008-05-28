#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../libs/defensiva.h"
#include"../libs/listActADT.h"
#include"../libs/graphADT.h"

struct activityCDT				/*Definida internamente.*/
{
	actInfo * info;
	stageADT dest;
	stageADT orig;
	int isFictitious;			/*1 si lo es, 0 lo contrario.*/
	int li, lt,ci, ct;
	activityADT next;
};

struct listActCDT
{
	activityADT head;
	listActADT tail;
};

listActADT 
NewActList(void)
{
	return NULL;
}

static int
CompareAct(activityADT act1, activityADT act2)
{
	return strcmp(act1->info->ID, act2->info->ID);
}

static int
CompareStr(char * ID, activityADT act)
{
	return strcmp(ID, act->info->ID);
}

/*
 * Funcion que InsertActa recursivamente la actividad en la lista.
 * En caso de error, retorna -1.
*/
static int
InsertActWrapped(listActADT * list, activityADT act)
{
	int aux;
	listActADT auxList = NULL;
	if(!ListActIsEmpty(*list) && (aux = CompareAct(act, ListActHead(*list))) > 0)
		return InsertActWrapped(&(*list)->tail, act);
	if(ListActIsEmpty(*list) || aux < 0)
	{
		auxList = *list;
		if((*list = malloc(sizeof(struct listActCDT))) == NULL)
			return -1;
		(*list)->head = act;
		(*list)->tail = auxList;
		return 1;
	}
	return 0;	/*La actividad ya existia en la lista.*/
}

int
InsertAct(listActADT * list, activityADT act)
{
	int aux;
	if((aux = InsertActWrapped(list, act)) == -1)
	{
		FreeActList (list);
		Error("No hay memoria suficiente como para enlistar ningun elemento mas.\n");
	}
	return aux;
}

int 
DeleteAct(listActADT * list, char * ID)
{
	int aux = 1;
	listActADT auxList;
	if(!ListActIsEmpty(*list) && (aux = CompareStr(ID, ListActHead(*list))) > 0)
		return DeleteAct(&(*list)->tail, ID);
	if(!aux)
	{
		auxList = *list;
		*list = ListActTail(*list);
		free(auxList);
		return 1;
	}	
	return 0;		/*El elemento no existia.*/		
}

int 
ListActIsEmpty(listActADT list)
{
	return (list == NULL);
}

activityADT 
ElementActBelongs(listActADT list, char * ID)
{
	int aux;
	if((aux = CompareStr(ID,ListActHead(list))) > 0)
		return ElementActBelongs(ListActTail(list), ID);
	if(!aux)
		return ListActHead(list);
	return NULL;
}

activityADT 
ListActHead(listActADT list)
{
	return list->head;
}

listActADT 
ListActTail(listActADT list)
{
	return list->tail;
}

activityADT 
ListActHeadID(listActADT list)
{
	return list->head->info->ID;	
}

void 
FreeActList (listActADT * list)
{
	if(*list)
	{
		FreeActList (&(*list)->tail);
		free(*list);
	}	
}
