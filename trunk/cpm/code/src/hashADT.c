#include<stdio.h>
#include<stdlib.h>
#include"../libs/hashADT.h"
#include"../libs/listADT.h"

struct actInfo
{
	char * descrip;
	int duracion;
	char * ID;
	char ** precedentes;
}

struct activityCDT
{
	struct actInfo * info;
	stageADT dest;
	stageADT orig;
	int tag, li, lt,ci, ct;
}

struct stageCDT
{
	int tag;
	int etapaID;
	listADT finalizan;
	listADT comienzan;
	stageADT next;
}

