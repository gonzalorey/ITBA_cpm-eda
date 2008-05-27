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

struct listCDT
{
	tElement element;
	listADT next;
};

listADT newList (void)
{
	return NULL;
}

int listIsEmpty (listADT list)
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
int insert (listADT* list, tElement element)
{
	listADT new, ant, rec;

	rec = ant = *list;

	while (!listIsEmpty(rec) && strcmp (rec->element->ID, element->ID))
	{
		ant = rec;
		rec = listTail (rec);
	}

	if (!listIsEmpty(rec) && !strcmp(rec->element->ID, element->ID))	/* Elemento repetido */
		return 0;

	/* llegue al final, si estoy en este punto el elemento no estaba en la lista */
	if ((new = malloc (sizeof(struct listCDT))) == NULL)
		Error ("No hay memoria disponible\n");

	new->element = element;
	new->next = NULL;
	
	if (ant == rec)
		*list = new;
	else
		ant->next = new;
	
	return 1;
}

char* getID (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->ID;
}

char* getDesc (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->description;
}

int getDur (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->duration;
}

char ** getPrec (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element->preced;
}

listADT listTail (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->next;
}

tElement listHead (listADT list)
{
	if (listIsEmpty(list))
		Error ("Lista vacia\n");

	return list->element;
}

static void freeStr (listADT list)
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

int delete (listADT* list, tElement element)
{
	listADT ant, rec;

	ant = rec = *list;

	while (!listIsEmpty(rec) && strcmp (rec->element->ID, element->ID))
	{
		ant = rec;
		rec = listTail (rec);
	}

	if (listIsEmpty(rec))
		return 0;		/* No está el elemento a eliminar */

	if (ant == rec)			/* Tengo que eliminar el primero */
		*list = listTail(*list);
	else
		ant->next = listTail(rec);
	
	freeStr (rec);
	return 1;
}

void freeList (listADT* list)
{
	listADT aux;

	while (!listIsEmpty(*list))
	{
		aux = listTail(*list);
		freeStr (*list);
		*list = aux;
	}

	*list = NULL;
}

