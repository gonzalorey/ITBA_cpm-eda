/* Lista simplemente encadenada sin hedaer, cuyos elementos son estructuras actInfo */

#include "../libs/listADT2.h"
#include <stdlib.h>
#include <stdio.h>

struct actInfo
{
	char * ID;
	char * description;
	int duration;
	char ** preced;
};

struct listInfCDT
{
	tElement element;
	listInfADT next;
};

listInfADT newInfList (void)
{
	return NULL;
}

int listInfIsEmpty (listInfADT list)
{
	return list == NULL;
}

static void Error (char * message)
{
	fprintf(stderr, message);
	exit (EXIT_FAILURE);
}

/* Ya que esta lista no inserta los elementos ordenados bajo ningun parametro, los voy poniendo al final ya que tengo que recorrer la lista
 * para chequear que no se inserte ningun elemento repetido
 */
int insertInf (listInfADT* list, tElement element)
{
	listInfADT new, ant, rec;

	rec = ant = *list;

	while (!listInfIsEmpty(rec) && strcmp (rec->element->ID, element->ID))
	{
		ant = rec;
		rec = listInfTail (rec);
	}

	if (!listInfIsEmpty(rec) && !strcmp(rec->element->ID, element->ID))	/* Elemento repetido */
		return 0;

	/* llegue al final, si estoy en este punto el elemento no estaba en la lista */
	if ((new = malloc (sizeof(struct listInfCDT))) == NULL)
		Error ("No hay memoria disponible\n");

	new->element = element;
	new->next = NULL;
	
	if (ant == rec)
		*list = new;
	else
		ant->next = new;
	
	return 1;
}

char* getIndID (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->ID;
}

char* getInfDesc (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->description;
}

int getInfDur (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->duration;
}

char ** getInfPrec (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->preced;
}

listInfADT listInfTail (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->next;
}

tElement listInfHead (listInfADT list)
{
	if (listInfIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element;
}

static void freeStr (listInfADT list)
{
	int i;

	free (list->element->ID);
	free (list->element->description);

	for (i = 0; *((list->element->preced)[i]); i++)
		free ((list->element->preced)[i]);

	free (list->element->preced);
	free (list->element);
	free (list);
}

int deleteInf (listInfADT* list, tElement element)
{
	listInfADT ant, rec;

	ant = rec = *list;

	while (!listInfIsEmpty(rec) && strcmp (rec->element->ID, element->ID))
	{
		ant = rec;
		rec = listInfTail (rec);
	}

	if (listInfIsEmpty(rec))
		return 0;		/* No está el elemento a eliminar */

	if (ant == rec)			/* Tengo que eliminar el primero */
		*list = listInfTail(*list);
	else
		ant->next = listInfTail(rec);
	
	freeStr (rec);
	return 1;
}

void freeInfList (listInfADT* list)
{
	listInfADT aux;

	while (!listInfIsEmpty(*list))
	{
		aux = listInfTail(*list);
		freeStr (*list);
		*list = aux;
	}

	*list = NULL;
}
