#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../libs/listADT.h"
#include"../libs/defensiva.h"

struct listCDT
{
	elementT head;
	listADT tail;
};

listADT 
NewList(void)
{
	return NULL;
}

static int
Compare(elementT elem1, elementT elem2)
{
	return strcmp(elem1->info->ID, elem2->info->ID);	
}

/*
 * Funcion que inserta recursivamente el elemento en la lista.
 * En caso de error, retorna -1.
*/
static int
InsertWrapped(listADT * list, elementT element)
{
	int aux;
	listADT auxList = NULL;
	if(!ListIsEmpty(*list) && (aux = Compare(element, ListHead(*list))) > 0)
		return InsertWrapped(&(*list)->tail, element);
	if(ListIsEmpty(*list) || aux > 0)
	{
		if(!ListIsEmpty(*list))
			auxList = ListTail(*list);
		if((*list = malloc(sizeof(struct listCDT))) == NULL)
			return -1;
		(*list)->head = element;
		(*list)->tail = auxList;
		return 1;
	}
	return 0;	/*El elemento ya existia en la lista.*/
}

int
Insert(listADT * list, elementT element)
{
	int aux;
	if((aux = InsertWrapped(list, element)) == -1)
	{
		FreeList(list);
		Error("No hay memoria suficiente como para enlistar algun elemento mas.\n");
	}
	return aux;
}

int 
Delete(listADT * list, elementT element)
{
	int aux = 1;
	listADT auxList;
	if(!ListIsEmpty(*list) && (aux = Compare(element, ListHead(*list))) < 0)
	{
		auxList = ListTail(*list);
		return Delete(&auxList, element);
	}
	if(!aux)
	{
		auxList = ListTail(*list);
		free(*list);
		*list = auxList;
	}	
	return 0;		/*El elemento no existia.*/		
}

int 
ListIsEmpty(listADT list)
{
	return (list == NULL);
}

int 
ElementBelongs(listADT list, elementT element)
{
	if(Compare(element,ListHead(list)) < 0)
		return ElementBelongs(ListTail(list), element);
	return (Compare(element,ListHead(list)) == 0);
}

elementT 
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
	listADT aux;
	if(*list)
	{
		aux = ListTail(*list);
		FreeList(&aux);
		free(*list);
	}	
}
