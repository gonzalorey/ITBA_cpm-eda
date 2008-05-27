#ifndef	__LISTADT_H_
#define	__LISTADT_H_

typedef struct actInfo*	tElement;
typedef	 struct listCDT*	listADT;

listADT newList (void);
int insert (listADT* list, tElement element);
listADT listTail (listADT list);
tElement listHead (listADT list);
int delete (listADT* list, tElement element);
void freeList (listADT* list);
char* getID (listADT list);
char* getDesc (listADT list);
int getDur (listADT list);
char ** getPrec (listADT list);
int replace (listADT list, tElement element);

#endif

