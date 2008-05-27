#include<stdio.h>
#include<stdlib.h>
#include"../libs/graphBuilder.h"
#include"../libs/graphADT.h"
/*#include"../libs/listADT.h"				lista con activityADT's*/
#include"../libs/listADT2.h"			/*lista con actInfo's*/

typedef struct						/*Definida para uso interno.*/
{
	char * descrip;
	int duracion;
	char * ID;
	char ** precedencies;
}actInfo;

graphADT
BuildPreliminarGraph(listADT list)
{
	graphADT g = NewGraph();
	actInfo * info;
	stageADT stg = NULL;
	listADT dcp;			/*Lista de precedentes creados que llegan al sumidero. Drain Connected Precendences.*/
	listADT ndcp;			/*Lista de precedentes creados que no llegan al sumidero. Not Drain Connected Precedences.*/
	listADT mergeList;
	listADT auxList = list;
	activityADT act;
	while(!listIsEmpty(auxList))
	{ 
		info = listHead(list);
		act = InsertActivity(g, info, NULL, GetDrain(g));			/*Creo la actividad y la conecto al sumidero.*/
			
		SetPrecedencesLists(&dcp, &ndcp, info->precedencies);		/*Armo las listas.*/
		if(!listIsEmpty(ndcp))
		{
			if(stg == NULL)
			{
				stg = InsertStage(g);
				SetActivityOrig(g, info->ID, stg);					/*Setea al nodo nuevo como origen de la actividad.*/
			}
			mergeList = MergeLists(ndcp, info->precedencies);
			MagicMagic(g, auxList);									/*No se que nombre ponerle.*/
		}
		if(!listIsEmpty(dcp))
		{
			if(stg == NULL)
				stg = InsertStage(g);
			ConnectPrecActDrain(dcp, stg);				/*Sus precedencias que terminaban en el sumidero, ahora apuntan a la nueva act.*/
		}
		if(stg == NULL && IsSourcePrec(info->precedencies))		/*Si la fuente esta como precedencia, la conecto con ella.*/
			SetActivityOrig(g, info->ID, GetSource(g));
		stg = NULL;
		auxList = listTail(list);
	}
}


MagicMagic(graphADT g)
{
	
}

graphADT
Optimize(graphADT g, listADT list)
{
	listADT auxList;
	actInfo * info;
	while(!listIsEmpty(list))
	{
		info = listHead(list);
		if(CompareLists(info->precedencies, GetStageFinish(GetActivityOrig(g, info->ID))))
			
	}
}