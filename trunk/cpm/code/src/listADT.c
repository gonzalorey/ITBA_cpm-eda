#include<stdio.h>
#include<stdlib.h>
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

int 
Insert(listADT * list, elementT element)
{
	listADT aux = *list;
	while(aux && Compare(element, ListHead(aux) < 0))
		aux = ListTail(aux);
	if(!aux || Compare(element,ListHead(aux) > 0))
		if((aux = malloc(sizeof(struct listCDT))) == NULL)
		{
			FreeList(list);
			Error()
}

int 
Delete(listADT * list, elementT element)
{
	
}

int 
ListIsEmpty(listADT list)
{
	
}

int 
ElementBelongs(listADT list, elementT element)
{
	
}

elementT 
ListHead(listADT list)
{
	
}

listADT 
ListTail(listADT list)
{

}
void 
FreeList(listADT * list)
{
	
}
