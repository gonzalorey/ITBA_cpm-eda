#ifndef GRAPHBUILDER_H_
#define GRAPHBUILDER_H_

#define BLOQUE 10

/*
 * Arma el grafo para graficar.
 */
graphADT BuildPreliminarGraph(listADT list);

/*
 * Arma 3 listas:
 * 		ncp 	= Non Created Precedencies
 * 		dcp 	= Drain Connected Precedencies
 * 		ndcp 	= Non Drain Connected Precedencies
 * Las mismas las arma con cada una de las actividades que preceden a tal actividad.
 */
void SetPrecedencesLists(graphADT g, lisInfADT list, listInfADT * ncp, listInfADT * dcp, listInfADT * ndcp, char ** precedencies);

/*
 * Reserva memoria para un actInfo y retorna su direccion en su nombre.
 */
actInfo * CopyActInfo(actInfo * info);

/*
 * Reserva memoria para las precedencias, y retorna su direccion en su nombre.
 */
char ** CopyPrecedencies(char ** prec);

/*
 * Genera una lista con las precedencias en comun.
 */
listInfADT MergeLists(listInfADT list, char ** precedencies);

/*
 * No es trivial. GENERA LAS ACTIVIDADES FICTICIAS haciendo un tipo de magia =P.
 */
void CreateFictitious(graphADT g, listInfADT list);

/*
 * Conecta el destino de los precedentes de cierta actividad a la etapa recibida.
 */
void ConnectPrecDestStage(graphADT g, listInfADT list, stageADT stg);

/*
 * Dice si la fuente es un precedente de tal actividad.
 */
int IsSourcePrec(char ** precedencies);

/*
 * Optimiza el grafo, para que quede lindo y sin aristas ficticias de mas.
 */
graphADT Optimize(graphADT g, listInfADT list);

#endif /*GRAPHBUILDER_H_*/
