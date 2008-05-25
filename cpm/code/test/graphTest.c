#include<stdio.h>
#include<stdlib.h>
#include"../libs/graphADT.h"

int
main(void)
{
	graphADT g = NewGraph();
	stageADT stg1, stg2, stg3, stg4;
	activityADT act1, act2, act3, act4;
	actInfo info1 = {"sarasa", 2, "A"};
	actInfo info2 = {"sarasa", 5, "B"};
	actInfo info3 = {"sarasa", 5, "D"};
	actInfo info4 = {"sarasa", 5, "C"};
	stg1 = InsertStage(g);
	stg2 = InsertStage(g);
	stg3 = InsertStage(g);
	stg4 = InsertStage(g);
	act1 = InsertActivity(g, &info1, NULL, NULL);
	act2 = InsertActivity(g, &info2, stg1, stg2);
	act3 = InsertActivity(g, &info3, GetSource(g), GetDrain(g));
	act4 = InsertActivity(g, &info4, GetSource(g), stg1);
	printf("%s\n", (SetActivityOrig(g, "A", stg3))?":D":":(");
	printf("%s\n", (SetActivityDest(g, "A", GetDrain(g)))?":D":":(");
	printf("%s\n", (SetActivityOrig(g, "A", stg2))?":D":":(");
	DeleteStage(g, stg2);
	DeleteActivity(g, "B");
	FreeGraph(g);
	return 0;
}
