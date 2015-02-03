#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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