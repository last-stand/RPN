#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

Node * create_node(void *data){
	Node_ptr link = calloc(1,sizeof(Node));
	link->data = data;
	link->next = NULL;
	return link;
};

LinkedList createList(void){
	LinkedList list;
	list.head = NULL;
	list.tail = NULL;
	list.count = 0;
	return list;
};

int add_to_list(LinkedList *list,Node *node){
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

void *get_first_element(LinkedList list){
	return list.head;
};

void *get_last_element(LinkedList list){
	return list.tail;
};

void traverse(LinkedList list, Function fun){
	Node_ptr walker = list.head;
	while(walker != NULL){
		 fun(walker->data);
		 walker = walker->next;
	}
};

void * getElementAt(LinkedList list, int index){
	void *result = NULL;
	int counter;
	Node_ptr walker = list.head;
	if(index > list.count-1)
		return result;
	for(counter=0; counter<=index ;++counter){
		if(counter == index)
			result = walker->data;
		walker = walker->next;
	}
	return result;
};

int indexOf(LinkedList list, void *element){
	Node_ptr walker = list.head;
	int index = 0;
	while(walker != NULL){
		if(walker->data == element)
			return index;
		 ++index;
		 walker = walker->next;
	}
	return -1;
};

Node_ptr getNodeAt(LinkedList *list, int index){
	int counter;
	Node_ptr walker = list->head;
	if(index > list->count-1)
		return NULL;
	for(counter=0; counter<=index ;++counter){
		if(counter == index)
			return walker;
		walker = walker->next;
	}
	return NULL;
};

void* deleteHead(LinkedList *list, int index){
	void* data = list->head->data;
	(list->head == list->tail) && (list->tail = NULL);
	list->head = list->head->next;
	list->count -= 1;
	free(list->head);
	return data;
}

void *deleteTail(LinkedList *list, int index){
	void* data;
	Node_ptr walker = list->head, previous_node, target_node;
	previous_node = getNodeAt(list, index -1);
	target_node = getNodeAt(list, index);
	list->tail = previous_node;
	previous_node->next = NULL;
	list->count -= 1;
	data = target_node->data;
	free(target_node);
	return data;
}

void *deleteMiddle(LinkedList *list, int index){
	void* data;
	Node_ptr walker = list->head, previous_node, target_node;
	previous_node = getNodeAt(list, index -1);
	target_node = getNodeAt(list, index);
	previous_node->next = target_node->next;
	list->count -= 1;
	data = target_node->data;
	free(target_node);
	return data;
}

void * deleteElementAt(LinkedList *list, int index){
	Node_ptr walker = list->head, previous;
	if(index > list->count-1) return NULL;
	if(index == 0)	return deleteHead(list,index);
	if(index == list->count-1)
		return deleteTail(list,index);
	else
		return deleteMiddle(list,index);
};

int asArray(LinkedList list, void **array){
	Node_ptr walker = list.head;
	int counter = 0;
	if(list.count == 0) return 0;
	while(walker != NULL){
		 array[counter] = walker->data;
		 walker = walker->next;
		 counter++;
	}
	return counter;
};

LinkedList * filter(LinkedList list, filterFunction function){
	LinkedList_ptr result_list_ptr;
	Node_ptr node_ptr, walker;
	LinkedList result_list = createList();
	result_list_ptr = &result_list;
	for(walker = list.head; walker != NULL; walker = walker->next){
		if(function(walker->data)){
			if(result_list.head==NULL)
				result_list.head = result_list.tail = create_node(walker->data);
			else{
				node_ptr = create_node(walker->data);
				result_list.tail->next = node_ptr;  
				result_list.tail =  node_ptr;
			}
		}
	}
	return result_list_ptr;
};