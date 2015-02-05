#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rpn.h"

int checkOpertaor(char operator){
	return operator=='+'|| operator=='-'|| operator=='*'|| operator=='/'|| operator=='^';
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

RPNList create_List(void){
	RPNList list;
	list.head = NULL;
	list.tail = NULL;
	list.count = 0;
	return list;
};

int add_to_RPNlist(RPNList *list,RPNNode *node){
	if(list->head == NULL){
		list->head = node;
		list->tail = node;
		list->count = 1;
		return 1;
	}
	list->tail->next = node;
	list->tail = node;
	list->count += 1;
	if(list->count > 0)
		return 1;
	return 0;
};

RPNNode_ptr createRPN_node(int start, int end){
	RPNNode_ptr rpn_node = calloc(1,sizeof(RPNNode));
	rpn_node->begin = start;
	rpn_node->end = end;
	rpn_node->data = NULL;
	rpn_node->RPNFunction = NULL;
	rpn_node->next = NULL;
	return rpn_node;
};

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
	if (checkOpertaor(expression[*index])){
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

int evaluate(char *expression){
	int a, b, result;
	int i, length = strlen(expression);
	char *numStr = (char*)calloc(8,sizeof(char));
	Stack stack = createStack();
	for(i=0; i<length; i++){
		if (expression[i] != ' '){
	        if (checkOpertaor(expression[i])){
	        	b = atoi((char*)pop(stack));
	            a = atoi((char*)pop(stack));
	            sprintf(numStr,"%d",operation(expression[i], a, b)); //converting int to string
	            push(stack, numStr);
	        }
	        else {
	       		push(stack,&expression[i]);
	        }
	    }   
	}
	result = atoi((char*)(*stack.top)->data);
	free(numStr);
	return result;
};