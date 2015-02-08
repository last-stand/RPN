#include "StackLibrary.h"

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
RPNList_ptr create_List(void);

typedef struct result Result;

struct result {
  int error;
  int status;
};

RPNNode_ptr createRPN_node(int start, int end);
int add_to_RPNlist(RPNList *list,RPNNode *node);
int isOpertaor(char operator);
void checkNumber(int* index, char* expression, RPNList* list);
void checkWhiteSpaces(int* index, char* expression, RPNList* list);
void checkOperator(int* index, char* expression, RPNList* list);
void getNumber(char* expression,RPNNode_ptr rpnNode);
void getOperator(char* expression,RPNNode_ptr rpnNode);
RPNList * createRPNList(char* expression);
int listEvaluator(Stack stack,RPNNode_ptr walker,RPNList_ptr rpn_list);
int checkError(RPNList_ptr rpn_list);
Result evaluate(char *expression);

char * infixToPostfix(char * expression);