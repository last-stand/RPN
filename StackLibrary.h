#include "linkedList.h"

typedef struct rpn_node RPNNode;
typedef RPNNode* RPNNode_ptr;
struct rpn_node{
	int begin;
	int end;
	void *data;
	void* (*RPNFunction)(char *,RPNNode_ptr);
	RPNNode *next;
};
typedef struct rpn_list
{
	int count;
	RPNNode_ptr head;
	RPNNode_ptr tail;
}RPNList;
typedef RPNList* RPNList_ptr;
RPNList create_List(void);


typedef struct stack Stack;
struct stack{
	LinkedList_ptr list;
	Node_ptr* top;
};
Stack createStack(void);
int push(Stack, void *);
void * pop(Stack );
void printStack(Stack stack);