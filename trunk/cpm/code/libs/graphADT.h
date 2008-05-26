#ifndef GRAPHADT_H_
#define GRAPHADT_H_

typedef struct					/*Definida para uso interno.*/
{
	char * descrip;
	int duracion;
	char * ID;
	char ** precedentes;
}actInfo;

/*Tipos de datos.*/
typedef struct graphCDT * graphADT;				/*Grafo.*/
typedef struct activityCDT * activityADT;		/*Actividades.*/
typedef struct stageCDT * stageADT;				/*Etapas.*/

/* Funcion:						NewGraph
 * Uso:							graphADT g;
 * 								g = NewGraph();
 * ----------------------------------------------------------------------------------
 * Descripcion:					Inicializa el grafo. Debe usarse antes de usar
 * 								cualquier otra funcion del mismo.
 * 								Crea las etapas de source y drain.
 * ----------------------------------------------------------------------------------
 * Precondicion:				-
 * Postcondicion:				Grafo creado.
 */
graphADT NewGraph(void);

/* Funcion:						FreeGraph
 * Uso:							FreeGraph(g);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Libera la memoria reservada para las operaciones
 * 								con el graphADT.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo g previamente creado.
 * Postcondicion:				Grafo liberado.
 */
void FreeGraph(graphADT g);

/* Funcion:						InsertStage
 * Uso:							stageADT stg;
 * 								...
 * 								stg = InsertStage(g);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Inserta una etapa dentro del grafo. Una vez hecho
 * 								esto, retorna la recien creada. En caso de haber 
 * 								algun error, libera los recursos almacenados 
 * 								hasta el momento por el graphADT y luego finaliza
 * 								el programa.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado.
 * Postcondicion:				Etapa dentro del grafo.
 */
stageADT InsertStage(graphADT g);

/* Funcion:						InsertActivity
 * Uso:							activityADT act;
 * 								...
 * 								act = InsertActivity(g, info, NULL, NULL);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Crea una nueva actividad dentro del grafo que
 * 								contenga la informacion de la estructura info.
 * 								No pueden haber dos actividades iguales.
 * 								La funcion tambien recibe la etapa de origen, y
 * 								destino de la actividad, las cuales pueden ser
 * 								omitidas enviando NULL en lugar de ellas.
 * 								En caso de error, libera los recursos reservados
 * 								hasta el momento y finaliza la aplicacion.
 * 								Al finalizar, retorna la actividad recien crada,
 * 								y en caso de que ya existiera, retorna NULL.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. Estructura info valida.
 * Postcondicion:				Actividad insertada en el grafo.
 */
activityADT InsertActivity(graphADT g, actInfo * info, stageADT orig, stageADT dest);

/* Funcion:						GetActivity
 * Uso:							activityADT act;
 * 								...
 * 								act = GetActivity(g, "D");
 * ----------------------------------------------------------------------------------
 * Descripcion:					Retorna la actividad que se corresponda con el 
 * 								ID ingresado. En caso de que no este dentro del
 * 								grafo, retorna NULL.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo.
 * Postcondicion:				Actividad obtenida.
 */
activityADT GetActivity(graphADT g, char * ID);

/* Funcion:						ElementBelongs
 * Uso:							if(ElementBelongs(g, "F"))
 * ----------------------------------------------------------------------------------
 * Descripcion:					Si la actividad que se corresponde con el ID se
 * 								encuentra dentro del grafo, retorna 1. Caso 
 * 								contrario, retorna 0.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo.
 * Postcondicion:				-
 */
int ElementBelongsToGraph(graphADT g, char * ID);

/* Funcion:						IsSource
 * Uso:							if(IsSource(g, stg))
 * ----------------------------------------------------------------------------------
 * Descripcion:					Si la etapa stg es la fuente del grafo, retorna 1, 
 * 								sino, 0.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. Etapa valida.
 * Postcondicion:				-
 */
int IsSource(graphADT g, stageADT stg);

/* Funcion:						IsDrain
 * Uso:							if(IsDrain(g, GetActivityDest(g, "D")))
 * ----------------------------------------------------------------------------------
 * Descripcion:					Si la etapa stg es el sumidero del grafo, retorna 1,
 * 								caso contrario, 0.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. Etapa valida.
 * Postcondicion:				-
 */
int IsDrain(graphADT g, stageADT stg);

/* Funcion:						GetSource
 * Uso:							stg = GetSource(g);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Retorna la fuente del grafo.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado.	
 * Postcondicion:				-
 */
stageADT GetSource(graphADT g);

/* Funcion:						GetDrain
 * Uso:							stg = GetDrain(g);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Retorna el sumidero del grafo.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado.
 * Postcondicion:				-
 */
stageADT GetDrain(graphADT g);

/* Funcion:						SetActivityOrig
 * Uso:							SetActivityOrig(g, "A", stg);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Setea el origen de la actividad que se corresponde
 * 								con tal ID. En caso de que no exista dicha actividad,
 * 								retorna 0, caso contrario, 1.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo. Etapa valida.
 * Postcondicion:				-
 */
int SetActivityOrig(graphADT g, char * ID, stageADT stg);

/* Funcion:						SetActivityDest
 * Uso:							if(SetActivityDest(g, "B", stg))
 * ----------------------------------------------------------------------------------
 * Descripcion:					Setea el destino de la actividad que se corresponde
 * 								con el ID recibido. En caso de que la misma no	
 * 								exista, esta retorna 0, caso contrario, 1.
 * 								Si ya tenia un origen seteado, esta lo borra de los
 * 								que comiencen en esa etapa, y genera el nuevo origen
 * 								en la que corresponda.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo. Etapa valida.	
 * Postcondicion:				-
 */
int SetActivityDest(graphADT g, char * ID, stageADT stg);

/* Funcion:						GetActivityOrig
 * Uso:							GetActivityOrig(g, "C");
 * ----------------------------------------------------------------------------------
 * Descripcion:					Obtiene la etapa que precede a la actividad que se
 * 								corresponde el ID. En caso de que no exista,
 * 								retorna NULL.
 * 								Si ya tenia un destino seteado, esta lo borra de los  
 * 								que finalicen en esa etapa, y genera el nuevo destino
 * 								en la que corresponda.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo.
 * Postcondicion:				-
 */
stageADT GetActivityOrig(graphADT g, char * ID);

/* Funcion:						GetActivityDest
 * Uso:							SetActivityOrig(g, "A", GetActivityDest(g, "B"));
 * ----------------------------------------------------------------------------------
 * Descripcion:					Obtiene el destino de la activida que se corresponde
 * 								con el ID recibido. En caso de no existir, retorna
 * 								NULL.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo. 
 * Postcondicion:				-
 */
stageADT GetActivityDest(graphADT g, char * ID);

/* Funcion:						SetFictitious
 * Uso:							SetFictitious(g, "D");
 * ----------------------------------------------------------------------------------
 * Descripcion:					Setea la actividad que se corresponde con el ID
 * 								como ficticia. En caso de que la misma no exista,
 * 								retorna 0, caso contrario, 1.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nula.
 * Postcondicion:				-
 */
int SetFictitious(graphADT g, char * ID);

/* Funcion:						UnsetFictitious
 * Uso:							UnsetFictitious(g, "D");
 * ----------------------------------------------------------------------------------
 * Descripcion:					Setea la actividad que se corresponde con el ID
 * 								como no ficticia. En caso de que la misma no exista,
 * 								retorna 0, caso contrario, 1.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nula.
 * Postcondicion:				-
 */
int UnsetFictitious(graphADT g, char * ID);

/* Funcion:						NumberOfStages
 * Uso:							printf("%d", NumberOfStages(g));
 * ----------------------------------------------------------------------------------
 * Descripcion:					Retorna la cantidad de etapas insertadas hasta el 
 * 								momento. Tener en cuenta que despues de haber
 * 								hecho el New, las etapas source y drain ya estan
 * 								creadas, entonces retornaria 2. 
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado.
 * Postcondicion:				-
 */
int NumberOfStages(graphADT g);

/* Funcion:						NumberOfActivities
 * Uso:							if(NumberOfActivities(g))
 * ----------------------------------------------------------------------------------
 * Descripcion:					Retorna la cantidad de actividades definidas en el 
 * 								grafo.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente definido.
 * Postcondicion:				-
 */
int NumberOfActivities(graphADT g);

/* Funcion:						DeleteStage
 * Uso:							DeleteStage(g, stg);
 * ----------------------------------------------------------------------------------
 * Descripcion:					Borra una etapa del grafo. La misma no debe ser ni
 * 								la fuente, ni el sumidero. En caso de no poder
 * 								borrarla, retorna 0, sino, 1.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. Etapa valida.
 * Postcondicion:				Grafo sin la etapa.
 */
int DeleteStage(graphADT g, stageADT stg);

/* Funcion:						DeleteActivity
 * Uso:							DeleteActivity(g, "N");
 * ----------------------------------------------------------------------------------
 * Descripcion:					Borra la actividad que se corresponde con el ID
 * 								recibido. En caso de que la misma no exista,
 * 								retorna 0, sino, 1.
 * ----------------------------------------------------------------------------------
 * Precondicion:				Grafo previamente creado. ID no nulo.
 * Postcondicion:				Grafo sin la actividad.
 */
int DeleteActivity(graphADT g, char * ID);

#endif /*GRAPHADT_H_*/
