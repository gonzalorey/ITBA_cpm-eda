#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../libs/defensiva.h"
#include"../libs/listADT.h"
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

struct listCDT
{
	activityADT head;
	listADT tail;
};

listADT 
NewList(void)
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
 * Funcion que inserta recursivamente la actividad en la lista.
 * En caso de error, retorna -1.
*/
static int
InsertWrapped(listADT * list, activityADT act)
{
	int aux;
	listADT auxList = NULL;
	if(!ListIsEmpty(*list) && (aux = CompareAct(act, ListHead(*list))) > 0)
		return InsertWrapped(&(*list)->tail, act);
	if(ListIsEmpty(*list) || aux < 0)
	{
		auxList = *list;
		if((*list = malloc(sizeof(struct listCDT))) == NULL)
			return -1;
		(*list)->head = act;
		(*list)->tail = auxList;
		return 1;
	}
	return 0;	/*La actividad ya existia en la lista.*/
}

int
Insert(listADT * list, activityADT act)
{
	int aux;
	if((aux = InsertWrapped(list, act)) == -1)
	{
		FreeList(list);
		Error("No hay memoria suficiente como para enlistar ningun elemento mas.\n");
	}
	return aux;
}

int 
Delete(listADT * list, char * ID)
{
	int aux = 1;
	listADT auxList;
	if(!ListIsEmpty(*list) && (aux = CompareStr(ID, ListHead(*list))) > 0)
		return Delete(&(*list)->tail, ID);
	if(!aux)
	{
		auxList = *list;
		*list = ListTail(*list);
		free(auxList);
		return 1;
	}	
	return 0;		/*El elemento no existia.*/		
}

int 
ListIsEmpty(listADT list)
{
	return (list == NULL);
}

activityADT 
ElementBelongs(listADT list, char * ID)
{
	int aux;
	if((aux = CompareStr(ID,ListHead(list))) > 0)
		return ElementBelongs(ListTail(list), ID);
	if(!aux)
		return ListHead(list);
	return NULL;
}

activityADT 
ListHead(listADT list)
{
	return list->head;
}

listADT 
ListTail(listADT list)
{
	return list->tail;
}

void 
FreeList(listADT * list)
{
	if(*list)
	{
		FreeList(&(*list)->tail);
		free(*list);
	}	
}
