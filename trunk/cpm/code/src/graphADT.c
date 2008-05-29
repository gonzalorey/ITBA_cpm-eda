#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../libs/defensiva.h"
#include"../libs/graphADT.h"
#include"../libs/listActADT.h"

struct graphCDT
{
	stageADT source;			/*Fuente.*/
	stageADT drain;				/*Sumidero.*/
	activityADT activities;		/*Aristas.*/
	int stageNum;				/*Cantidad de nodos (etapas) del grafo.*/
	int actNum;					/*Cantidad de aristas (actividades) del grafo.*/
}; 

struct activityCDT				/*Aristas del grafo.*/
{
	actInfo * info;
	stageADT dest;
	stageADT orig;
	int isFictitious;			/*1 si lo es, 0 lo contrario.*/
	activityADT next;
};

struct stageCDT					/*Nodos del grafo.*/
{
	int tag;
	listActADT finish;				/*Actividades que finalizan en esta etapa.*/
	listActADT start;				/*Actividades que comienzan en esta etapa.*/
	stageADT next;				/*Nodo siguiente.*/
	stageADT previous;			/*Nodo anterior.*/
};

graphADT 
NewGraph(void)
{
	graphADT rta;
	if((rta = calloc(1, sizeof(struct graphCDT))) == NULL)
		Error("No hay memoria suficiente como para crear el grafo.\n");
	if((rta->source = calloc(1, sizeof(struct stageCDT))) == NULL)
	{
		free(rta);
		Error("No hay memoria suficiente como para crear el grafo.\n");
	}
	if((rta->drain = calloc(1, sizeof(struct stageCDT))) == NULL)
	{
		free(rta->source);
		free(rta);
		Error("No hay memoria suficiente como para crear el grafo.\n");
	}
	rta->source->next = rta->drain;
	rta->drain->previous = rta->source;
	rta->stageNum = 2;						/*Source y drain ya insertados.*/
	return rta;
}

/*
 * Funcion que libera los stages.
 */
static void
FreeStages(stageADT stg)
{
	if(stg)
	{
		FreeStages(stg->next);
		FreeActList(&stg->start);
		FreeActList(&stg->finish);
		free(stg);	
	}
}

/*
 * Funcion que libera los activities.
 */
static void
FreeActivities(activityADT act)
{
	if(act)
	{
		FreeActivities(act->next);
		free(act);	
	}
}

void 
FreeGraph(graphADT g)
{
	FreeStages(g->source);
	FreeActivities(g->activities);
	free(g);
}

stageADT
InsertStage(graphADT g)
{
	stageADT stg, aux;
	if((stg = calloc(1, sizeof(struct stageCDT))) == NULL)
	{
		FreeGraph(g);
		Error("No hay memoria suficiente como para insertar otra etapa.\n");
	}
	aux = g->drain->previous;
	aux->next = stg;
	g->drain->previous = stg;
	stg->start = NewActList();
	stg->finish = NewActList();
	stg->next = g->drain;
	stg->previous = aux;
	g->stageNum++;
	return stg;
}

static int
Compare(actInfo * info1, actInfo * info2)
{
	return strcmp(info1->ID, info2->ID);	
}

static activityADT
InsertActivityWrapped(activityADT * act, actInfo * info)
{
	activityADT aux = *act;
	int cmp;
	if(!(*act) || (cmp = Compare((*act)->info, info)) > 0)
	{
		if((*act = calloc(1, sizeof(struct activityCDT))) == NULL)
		{
			*act = aux;
			return NULL;
		}
		(*act)->next = aux;
		(*act)->info = info;
		return *act;
	}
	else	/*Si acepta repetidos, para el caso de las ficticias.*/
		return InsertActivityWrapped(&(*act)->next, info);
}

activityADT
InsertActivity(graphADT g, actInfo * info, stageADT orig, stageADT dest)
{
	activityADT act;
	if((act = InsertActivityWrapped(&g->activities, info)) == NULL)
	{
		FreeGraph(g);
		Error("No hay memoria suficiente como para insertar otra actividad.\n");
	}
	act->orig = orig;
	act->dest = dest;
	if(orig)
		InsertAct(&orig->start, act);
	if(dest)
		InsertAct(&dest->finish, act);
	g->actNum++;
	return act;
}

/*
 * Retorna la direccion actividad que se corresponde con tal ID. 
 * Si no existe, devuelve NULL.
 */
static activityADT *
GetActivityWrapped(activityADT * act, char * ID)
{
	int cmp;
	if(*act && (cmp = strcmp((*act)->info->ID, ID)) < 0)
		return GetActivityWrapped(&(*act)->next, ID);
	else if(*act && !cmp)
		return act;
	else
		return NULL;		/*Si es mayor o si act == NULL, el elemento no esta.*/
}

activityADT
GetActivity(graphADT g, char * ID)
{
	activityADT * act = GetActivityWrapped(&g->activities, ID);
	return (*act);
}

int 
ElementBelongsToGraph(graphADT g, char * ID)
{
	return (GetActivity(g, ID) != NULL);
}

int
IsSource(graphADT g, stageADT stg)
{
	return (stg == g->source);	
}

int
IsDrain(graphADT g, stageADT stg)
{
	return (stg == g->drain);	
}

stageADT
GetSource(graphADT g)
{
	return g->source;	
}

stageADT
GetDrain(graphADT g)
{
	return g->drain;
}

int
SetActivityOrig(graphADT g, char * ID, stageADT stg)
{
	activityADT aux;
	if((aux = GetActivity(g, ID)) == NULL)
		return 0;
	if(aux->orig)							/*Si ya tenia un origen, la borro del mismo.*/
		Delete(&aux->orig->start, ID);
	aux->orig = stg;
	InsertAct(&stg->start, aux);
	return 1;
}

int
SetActivityDest(graphADT g, char * ID, stageADT stg)
{
	activityADT aux;
	if((aux = GetActivity(g, ID)) == NULL)
		return 0;
	if(aux->dest)							/*Si ya tenia un destino, la borro del mismo.*/
		Delete(&aux->dest->finish, ID);
	aux->dest = stg;
	InsertAct(&stg->finish, aux);
	return 1;
}

stageADT
GetActivityOrig(graphADT g, char * ID)
{
	activityADT aux;
	if((aux = GetActivity(g, ID)) == NULL)
		return NULL;
	return aux->orig;
}

stageADT
GetActivityDest(graphADT g, char * ID)
{
	activityADT aux;
	if((aux = GetActivity(g, ID)) == NULL)
		return NULL;
	return aux->dest;
}

stageADT
GetNextStage(stageADT stg)
{
	return stg->next;	
}

stageADT
GetPreviousStage(stageADT stg)
{
	return stg->previous;	
}

listActADT
GetStageStart(stageADT stg)
{
	return stg->start;	
}

listActADT
GetStageFinish(stageADT stg)
{
	return stg->finish;	
}

char * 
GetActivityInfo(graphADT g, activityADT act)
{
	return act->info;	
}

int
IsFictitious(graphADT g, char * ID)
{
	activityADT aux;
	if((aux = GetActivity(g, ID)) == NULL)
		return 0;
	return (aux->isFictitious == 1);
}

void
SetFictitious(graphADT g, activityADT act)
{
	act->isFictitious = 1;
}

int
UnsetFictitious(graphADT g, activityADT act)
{
	act->isFictitious = 0;
}

int
NumberOfStages(graphADT g)
{
	return g->stageNum;	
}

int
NumberOfActivities(graphADT g)
{
	return g->actNum;
}

/*
 * Borra los origenes de todas las actividades dentro de la lista.
 */
static void
DeleteActivitiesOrig(listActADT list)
{
	activityADT act;
	if(!ListActIsEmpty(list))
	{
		act = ListActHead(list);
		act->orig = NULL;
		DeleteActivitiesOrig(ListActTail(list));
	}	
}

/*
 * Borra los destinos de todas las actividades dentro de la lista.
 */
static void
DeleteActivitiesDest(listActADT list)
{
	activityADT act;
	if(!ListActIsEmpty(list))
	{
		act = ListActHead(list);
		act->dest = NULL;
		DeleteActivitiesDest(ListActTail(list));
	}	
}

int
DeleteStage(graphADT g, stageADT stg)
{
	if(IsSource(g, stg) || IsDrain(g, stg))
		return 0;					/*Ni la fuente ni el sumidero pueden ser borrados.*/
	stg->previous->next = stg->next;
	stg->next->previous = stg->previous;
	DeleteActivitiesOrig(stg->start);
	DeleteActivitiesDest(stg->finish);
	FreeActList(&stg->start);
	FreeActList(&stg->finish);
	free(stg);
	g->stageNum--;
	return 1;
}

int
DeleteActivity(graphADT g, char * ID)
{
	activityADT *act, aux;
	if((act = GetActivityWrapped(&g->activities, ID)) == NULL)
		return 0;
	if((*act)->orig)					/*La borro en las etapas.*/
		Delete(&(*act)->orig->finish, ID);	
	if((*act)->dest)
		Delete(&(*act)->dest->start, ID);
	aux = (*act);
	*act = (*act)->next;
	free(aux);
	g->actNum--;
	return 1;
}
