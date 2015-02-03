#include "linkedList.h"

typedef struct stack Stack;
struct stack{
	LinkedList_ptr list;
	Node_ptr* top;
};

typedef struct emp Employee;
struct emp{
	int id;
	char name[5];
};

Stack createStack(void);
int push(Stack, void *);
void * pop(Stack );