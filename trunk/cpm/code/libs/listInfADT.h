#ifndef	__LISTADT_H_
#define	__LISTADT_H_

typedef struct actInfo*	tElement;
typedef	 struct listInfCDT*	listInfADT;

listInfADT newInfList (void);
int insertInf (listInfADT* list, tElement element);
listInfADT listInfTail (listInfADT list);
tElement listInfHead (listInfADT list);
int deleteInf (listInfADT* list, tElement element);
void freeInfList (listInfADT* list);
char* getInfID (listInfADT list);
char* getInfDesc (listInfADT list);
int getInfDur (listInfADT list);
char ** getInfPrec (listInfADT list);
int replaceInf (listInfADT list, tElement element);

#endif

