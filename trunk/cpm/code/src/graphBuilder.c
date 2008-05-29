#include<stdio.h>
#include<stdlib.h>
#include"../libs/defensiva.h"
#include"../libs/graphBuilder.h"
#include"../libs/graphADT.h"
#include"../libs/listActADT.h"				/*lista con activityADT's	*/
#include"../libs/listInfADT.h"				/*lista con actInfo's		*/

typedef struct								/*Definida para uso interno.*/
{
	char * descrip;
	int duracion;
	char * ID;
	char ** precedencies;
}actInfo;

/*
 * Arma el grafo para graficar.
 */
graphADT
BuildPreliminarGraph(listADT list)
{
	graphADT g = NewGraph();
	actInfo * info, * auxInfo;
	stageADT stg = NULL;

/*Lista de precedentes insertados que llegan al sumidero. Drain Connected Precendences.*/
	listInfADT dcp;	

/*Lista de precedentes insertados que no llegan al sumidero. Non Drain Connected Precedences.*/
	listInfADT ndcp;

/*Lista de precedentes no creados. Non Created Precedences.*/
	listInfADT ncp;	

	listInfADT mergeList;
	listInfADT auxList = list;	/*Se recorrera sobre esta lista.*/
	activityADT act, auxAct;

	while(!listInfIsEmpty(auxList))
	{ 
		
		dcp = newInfList();					/*Inicializo las listas.*/
		ndcp = newInfList();
		ncp = newInfList();
		mergeList = newInfList();
		
		info = listInfHead(list);
		act = InsertActivity(g, info, NULL, GetDrain(g));			/*Creo la actividad y la
																	conecto al sumidero.*/
		if(strcmp(info->precedencies[0], "Fuente"))				
		{								/*Si las precedencias NO son la fuente*/						
			stg = InsertStage(g);		/*genero una nueva etapa y la conecto a ella.*/
			SetActivityOrig(g, info->ID, stg);
		}
		SetPrecedencesLists(g, list, &ncp, &dcp, &ndcp, info->precedencies);		/*Armo las listas.*/
		
		if(!listInfIsEmpty(ncp))
		{
			stg = InsertStage(g);
			while(!listInfIsEmpty(ncp))
			{
				auxInfo = listInfHead(ncp);
				auxAct = InsertActivity(g, auxInfo, NULL, stg);
				ncp = listInfTail(ncp);
			}
		}
		if(!listInfIsEmpty(ndcp))
		{
			if(stg == NULL)
			{
				stg = InsertStage(g);					/*Setea al nodo nuevo*/
				SetActivityOrig(g, info->ID, stg);		/*como origen de la actividad.*/	
			}
			mergeList = MergeLists(ndcp, info->precedencies);
			CreateFictitious(g, mergeList);
		}
		if(!listInfIsEmpty(dcp))
		{
			if(stg == NULL)
				stg = InsertStage(g);	/*Sus precedencias que terminaban en el sumidero*/
			ConnectPrecDestStage(g, dcp, stg);	/*ahora apuntan a la nueva act.*/	
		}
		if(stg == NULL && IsSourcePrec(info->precedencies))	/*Si la fuente esta como*/
			SetActivityOrig(g, info->ID, GetSource(g));	/*precedencia, la conecto con ella.*/
		stg = NULL;
		auxList = listInfTail(list);
		
		freeInfList(&dcp);
		freeInfList(&ndcp);
		freeInfList(&ncp);
		freeInfList(&mergeList);
	}
}

/*
 * Arma 3 listas:
 * 		ncp 	= Non Created Precedencies
 * 		dcp 	= Drain Connected Precedencies
 * 		ndcp 	= Non Drain Connected Precedencies
 * Las mismas las arma con cada una de las actividades que preceden a tal actividad.
 */
void
SetPrecedencesLists(graphADT g, lisInfADT list, listInfADT * ncp, listInfADT * dcp, listInfADT * ndcp, char ** precedencies)
{
	int i = 0;
	activityADT act;
	actInfo * info;
	listActADT actList;
	while(precedencies[i])
	{
		info = CopyActInfo(getActInfo(list, precedencies[i]));
		if((act = GetActivity(g, precedencies[i])) == NULL)
			insertInf(ncp, info);
		else
		{
			actList = GetStageStart(GetActivityOrig(g, precedencies[i]));
			while(!ListActIsEmpty(actList))
			{Act
				act = ListHeader(actList);
				if(IsDrain(GetActivityDest(g, ListActHeadID(list))))
					insertInf(dcp, info);
				else
					insertInf(ndcp, info);	
				actList = ListTail(actList);
			}
		}
		i++;
	}
}

/*
 * Reserva memoria para un actInfo y retorna su direccion en su nombre.
 */
actInfo *
CopyActInfo(actInfo * info)
{
	actInfo * rta;
	if((calloc(1, sizeof(actInfo))) == NULL)
		Error("No hay memoria suficiente como para crear otra actividad.\n");
	if((rta->descrip = malloc(strlen(info->descrip)))== NULL)
	{
		free(rta);
		Error("No hay memoria suficiente como para crear otra actividad.\n");	
	}
	if((rta->ID = malloc(strlen(info->ID))) == NULL)
	{
		free(rta->descrip);
		free(rta);
		Error("No hay memoria suficiente como para crear otra actividad.\n");	
	}
	if((rta->precedencies = CopyPrecedencies(info->precedencies)) == NULL)
	{
		free(rta->descrip);
		free(rta->ID);
		free(rta);
		Error("No hay memoria suficiente como para crear otra actividad.\n");	
	}
	strcpy(rta->descrip, info->descrip);
	strcpy(rta->ID, info->ID);
	rta->duracion = info->duracion;
	return rta;
}

/*
 * Reserva memoria para las precedencias, y retorna su direccion en su nombre.
 */
char **
CopyPrecedencies(char ** prec)
{
	int i = 0;
	char ** rta = NULL, aux;
	while(prec[i])
	{
		if(i % BLOQUE == 0)
		{
			if((aux = realloc(rta, sizeof(char *))) == NULL)
			{
				FreePrec(rta, i);
				return NULL;
			}
			rta = aux;
		}
		if((rta[i] = malloc(strlen[i])) == NULL)
		{
			FreePrec(rta, i);
			return NULL;
		}
		strcpy(rta[i], prec[i++]);		
	}
	return realloc(rta, i);
}

/*
 * Genera una lista con las precedencias en comun.
 */
listInfADT
MergeLists(listInfADT list, char ** precedencies)
{
	int i = 0;
	listInfADT rta = NewList();
	actInfo * info, * auxInfo;
	while(precedencies[i])
	{
		if((info = getActInfo(list, precendencies[i])) != NULL)
		{
			auxInfo = CopyActInfo(info);
			insertInf(&rta, auxInfo);
		}
		i++;
	}
}

/*No es trivial. GENERA LAS ACTIVIDADES FICTICIAS haciendo un tipo de magia =P.*/
void
CreateFictitious(graphADT g, listInfADT list)
{
	/*Tambien recibo una lista con los precedentes que terminan en el origen de la actividad actual???*/
}

/*
 * Conecta el destino de los precedentes de cierta actividad a la etapa recibida.
 */
void
ConnectPrecDestStage(graphADT g, listInfADT list, stageADT stg)
{
	listInfADT aux = list;
	while(!listInfIsEmpty(aux))
	{
		SetActivityDest(g, getInfID(list), stg);
		aux = listInfTail(aux);
	}
}

/*
 * Dice si la fuente es un precedente de tal actividad.
 */
int
IsSourcePrec(char ** precedencies)
{
	int i = 0;
	while(precedencies[i])
		if(strcmp(precedencies[i++], "Fuente"))
			return 1;
	return 0;
}

/*
 * Optimiza el grafo, para que quede lindo y sin aristas ficticias de mas.
 */
graphADT
Optimize(graphADT g, listInfADT list)
{
	actInfo * info;
	stageADT stg, stgAux;
	listActADT listAct, listAux;
	activityADT act;
	stg = GetSource(g)			/*No hay actividades que terminen en la fuente.*/
	do				
	{
		stg = GetNextStage(stg);
		listAct = GetStageFinish(stg);		/*Obtengo los que finalizan en esta etapa.*/
		while(!ListActIsEmpty(listAct))
		{
			listAux = ListActTail(listAct);
			while(!ListActIsEmpty(listAux))
			{
				if((act = ListActHead(listAux)) == ListActHead(listAct))
				{
					/*A las actividades que comienzan en la misma etapa, les genero una ficticia y les cambio el dest.*/
					stgAux = InsertStage(g);
					info = GetActivityInfo(g, act);
					SetActivityOrig(g, info->ID, stgAux);	/*La act se elimina de la lista de act que finalizan en tal nodo
															y se inserta en otra automanticamente. Por esto mismo, no es 
															necesario pedir el ListTail.*/
					act = InsertActivity(g, info, stgAux, stg);	/*Origen el nuevo nodo, destino, el evaluado actualmente.*/
					SetFictitious(g, act);
				}
				else
					listAux = ListActTail(listAux);
			}
			listAct = ListActTail(listAct);
		}
	}
	while(!IsDrain(g, stg));		/*Mientras que no sea el sumidero, me fijo los que finalizan en el.*/
	return g;
} 
