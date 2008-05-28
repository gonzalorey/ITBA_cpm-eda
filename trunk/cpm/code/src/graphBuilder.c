#include<stdio.h>
#include<stdlib.h>
#include"../libs/graphBuilder.h"
#include"../libs/graphADT.h"
#include"../libs/listActADT.h"				/*lista con activityADT's	*/
#include"../libs/listInfADT.h"				/*lista con actInfo's		*/

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
	actInfo * info, * auxInfo;
	stageADT stg = NULL;

/*Lista de precedentes creados que llegan al sumidero. Drain Connected Precendences.*/
	listInfADT dcp;	

/*Lista de precedentes creados que no llegan al sumidero. Not Drain Connected Precedences.*/
	listInfADT ndcp;

/*Lista de precedentes no creados. Non Created Precedences.*/
	listInfADT ncp;	

	listInfADT mergeList;
	listInfADT auxList = list;	/*Se recorrera sobre esta lista.*/
	listInfADT infoList;		/*Se recorrera los ncp con esta lista.*/
	activityADT act, auxAct;

	while(!listInfIsEmpty(auxList))
	{ 
		info = listInfHead(list);
		act = InsertActivity(g, info, NULL, GetDrain(g));			/*Creo la actividad y la
											conecto al sumidero.*/
		if(strcmp(info->precedencies[0], "Fuente"))				
		{						/*Si las precedencias no son la fuente
								genero una nueva etapa y la conecto a ella.*/
			stg = InsertStage(g);
			SetActivityOrig(g, info->ID, stg);
		}
		SetPrecedencesLists(&ncp, &dcp, &ndcp, info->precedencies);		/*Armo las listas.*/
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
				stg = InsertStage(g);			/*Setea al nodo nuevo*/
				SetActivityOrig(g, info->ID, stg);	/*como origen de la actividad.*/	
			}
			mergeList = MergeLists(ndcp, info->precedencies);
			CreateFictitious(g, mergeList);
		}
		if(!listInfIsEmpty(dcp))
		{
			if(stg == NULL)
				stg = InsertStage(g);	/*Sus precedencias que terminaban en el sumidero*/
			ConnectPrecActDrain(dcp, stg);	/*ahora apuntan a la nueva act.*/	
		}
		if(stg == NULL && IsSourcePrec(info->precedencies))	/*Si la fuente esta como*/
			SetActivityOrig(g, info->ID, GetSource(g));	/*precedencia, la conecto con ella.*/
		stg = NULL;
		auxList = listInfTail(list);
	}
}


CreateFictitious(graphADT g, listInfADT list)
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
