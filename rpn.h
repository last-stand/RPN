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
RPNList create_List(void);
RPNNode_ptr createRPN_node(int start, int end);
int checkOpertaor(char);
void checkNumber(int* index, char* expression, RPNList* list);
void checkWhiteSpaces(int* index, char* expression, RPNList* list);
void checkOperator(int* index, char* expression, RPNList* list);
void getNumber(char* expression,RPNNode_ptr rpnNode);
void getOperator(char* expression,RPNNode_ptr rpnNode);
RPNList * createRPNList(char* expression);

int evaluate(char *expression);