#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rpn.h"

int isOpertaor(char operator){
	char *operatorString = "+-*/^";
	int i;
	for(i=0; i < strlen(operatorString); i++){
		if(operator==operatorString[i])
			return 1;
	}
	return 0;
};

int operation(char expression,int number1,int number2){
	int result;
	switch (expression) {             
		case '+': result = number1 + number2;
		break;
		case '-': result = number1 - number2;
		break;
		case '*': result = number1 * number2;
		break;
		case '/': result = number1 / number2;
		break;
	}
	return result;
}


void getNumber(char* expression,RPNNode_ptr rpnNode){
	char number[rpnNode->end - rpnNode->begin+2];
	int i,j=0;
	for(i=rpnNode->begin; i <= rpnNode->end; i++,j++){
		number[j] = expression[i];
	}
	rpnNode->data = malloc(sizeof(int));
	*(int*)(rpnNode->data) = atoi(number);
}

void getOperator(char* expression,RPNNode_ptr rpnNode){
	rpnNode->data = malloc(sizeof(char));
	*(char*)(rpnNode->data) = expression[rpnNode->begin];
}

void checkNumber(int *index, char* expression, RPNList* list){
	int start = *index;
	RPNNode_ptr rpn_node = NULL;
	while(expression[*index] >= '0' && expression[*index] <= '9'){
		(rpn_node == NULL) && (rpn_node = createRPN_node(start,*index));
		rpn_node->end = *index;
		*index += 1;
	}
	(start < *index) && (*index -= 1);
	if(rpn_node != NULL){
		add_to_RPNlist(list, rpn_node);
		getNumber(expression,rpn_node);
	}
}

void checkOperator(int *index, char* expression, RPNList* list){
	RPNNode_ptr rpn_node = NULL;
	if (isOpertaor(expression[*index])){
		(rpn_node == NULL) && (rpn_node = createRPN_node(*index,*index));
	}
	if(rpn_node != NULL){
		add_to_RPNlist(list, rpn_node);
		getOperator(expression,rpn_node);
	}
}

RPNList * createRPNList(char* expression){
	RPNList_ptr rpn_list = calloc(1,sizeof(RPNList));
	int i, length = strlen(expression);
	*rpn_list = create_List();
	for(i=0; i<length; i++){
		checkNumber(&i, expression, rpn_list);
		checkOperator(&i, expression, rpn_list);
	}
	return rpn_list;
}

void freeAllNodes(RPNList_ptr rpn_list){
	RPNNode_ptr walker = rpn_list->head;
	while(walker != NULL){
		if(walker->data != NULL) free(walker->data);
		free(walker);
		walker = walker->next;
	}
}

int listEvaluator(Stack stack,RPNNode_ptr walker,RPNList_ptr rpn_list){
	void * a, * b;
	int *numStr = (int*)calloc(1,sizeof(int)), result;
	walker = rpn_list->head;
	while(walker != NULL){
        if (isOpertaor(*(char*)walker->data)){
        	b = pop(stack);	a = pop(stack);
            *(int*)numStr = operation(*(char*)walker->data, *(int*)a, *(int*)b);
            push(stack, numStr);
        }
        else 
       	   push(stack,walker->data);
        walker = walker->next;
	}
	result = *(int*)(*stack.top)->data;
	free(numStr);
	return result;
}

int evaluate(char *expression){
	int result;
	RPNNode_ptr walker;
	Stack stack = createStack();
	RPNList_ptr rpn_list = createRPNList(expression);
    result = listEvaluator(stack,walker,rpn_list);
    freeAllNodes(rpn_list);
    return result;
};