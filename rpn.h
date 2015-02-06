#include "StackLibrary.h"

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
int evaluate(char *expression);