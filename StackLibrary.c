#include "StackLibrary.h"
#include <stdio.h>
#include <stdlib.h>

Stack createStack(void){
	LinkedList *list=calloc(sizeof(LinkedList),1);
	Stack stack={list,&list->tail};
	return stack;
};

int push(Stack stack, void *data){
	Node_ptr node = create_node(data);
	add_to_list(stack.list, node);
	if(stack.list->count == 0) return -1;
	return stack.list->count;
};

void * pop(Stack stack){
	return deleteElementAt(stack.list, stack.list->count-1);
};

void printStack(Stack stack){
	Node_ptr walker = stack.list->head;
	while(walker != NULL){
		 printf("%d\n",*(int*)walker->data);
		 walker = walker->next;
	}
};