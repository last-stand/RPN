#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>

RPNList_ptr create_List(void){
	RPNList_ptr list = calloc(1, sizeof(RPNList));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
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