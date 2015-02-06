#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>

char *expression;
int result;
RPNList list;
RPNList_ptr npr_list = &list;

void test_isOpertaor_should_return_1_for_valid_operator_for_RPN(){
	assertEqual(isOpertaor('+'),1);
	assertEqual(isOpertaor('-'),1);
	assertEqual(isOpertaor('/'),1);
	assertEqual(isOpertaor('*'),1);
	assertEqual(isOpertaor('^'),1);
}

void test_isOpertaor_should_return_0_for_invalid_operator_for_RPN(){
	assertEqual(isOpertaor('$'),0);
	assertEqual(isOpertaor('A'),0);
	assertEqual(isOpertaor('2'),0);
	assertEqual(isOpertaor('%'),0);
}


void test_checkNumber_should_get_start_and_end_index_of_continuous_number_in_node_from_string(){
	int index = 0;
	expression = "1223";
	list = create_List();
	checkNumber(&index, expression, &list);
	assertEqual(list.head->begin,0);
	assertEqual(list.head->end,3);
	free(list.head);
}

void test_checkNumber_should_not_create_node_if_found_space_before_number(){
	int index = 0;
	expression = "   123";
	list = create_List();
	checkNumber(&index, expression, &list);
	assert(list.head == NULL);
	assert(list.tail == NULL);
	free(list.head);
}

void test_checkNumber_should_not_create_node_if_found_operator_before_number(){
	int index = 0;
	expression = "+   123";
	list = create_List();
	checkNumber(&index, expression, &list);
	assert(list.head == NULL);
	assert(list.tail == NULL);
	free(list.head);
}

void test_checkNumber_should_give_start_and_end_index_of_continuous_number_and_avoid_spaces(){
	int index = 0;
	expression = "12345  ";
	list = create_List();
	checkNumber(&index, expression, &list);
	assertEqual(list.head->begin,0);
	assertEqual(list.head->end,4);
	free(list.head);
}

void test_checkNumber_should_give_start_and_end_as_same_index_if_there_is_only_single_number(){
	int index = 0;
	expression = "1  ";
	list = create_List();
	checkNumber(&index, expression, &list);
	assertEqual(list.head->begin,0);
	assertEqual(list.head->end,0);
	free(list.head);
}

void test_checkNumber_should_give_start_and_end_from_any_index_of_string(){
	int index = 3;
	expression = "   1234  ";
	list = create_List();
	checkNumber(&index, expression, &list);
	assertEqual(list.head->begin,3);
	assertEqual(list.head->end,6);
	free(list.head);
}

void test_checkNumber_should_give_same_end_and_given_index_(){
	int index = 4;
	expression = "    1234  ";
	list = create_List();
	checkNumber(&index, expression, &list);
	assertEqual(list.head->begin,4);
	assertEqual(list.head->end,7);
	assertEqual(list.head->end,index);
	free(list.head);
}

void test_checkOperator_should_create_node_if_it_found_operator(){
	int index = 0;
	expression = "+  123";
	list = create_List();
	checkOperator(&index, expression, &list);
	assert(list.head->begin == 0);
	assert(list.head->end == 0);
	free(list.head);
}

void test_checkOperator_should_create_node_if_it_found_operator_at_middle_index(){
	int index = 3;
	expression = "12 * 4";
	list = create_List();
	checkOperator(&index, expression, &list);
	assert(list.head->begin == 3);
	assert(list.head->end == 3);
	free(list.head);
}


void test_checkOperator_should_not_create_node_if_it_found_number(){
	int index = 1;
	expression = " 124";
	list = create_List();
	checkOperator(&index, expression, &list);
	assert(list.head == NULL);
	assert(list.tail == NULL);
	free(list.head);
}

void test_checkOperator_should_not_create_node_if_it_found_spaces(){
	int index = 2;
	expression = "12 * 4";
	list = create_List();
	checkOperator(&index, expression, &list);
	assert(list.head == NULL);
	assert(list.tail == NULL);
	free(list.head);
}

void test_checkOperator_should_work_for_single_operator_at_a_time(){
	int index = 5;
	expression = "12 2 +-";
	list = create_List();
	checkOperator(&index, expression, &list);
	index++;
	checkOperator(&index, expression, &list);
	assert(list.head->begin=5);
	assert(list.head->end=5);
	assert(list.tail->begin=6);
	assert(list.tail->end=6);
	free(list.head);
	free(list.tail);
}

void test_getNumber_should_give_number_from_string_type_to_number(){
	int index = 0;
	void * data;
	expression = "123";
	list = create_List();
	checkNumber(&index, expression, &list);
	getNumber(expression,list.head);
	assertEqual(*(int*)list.head->data,123);
	free(list.head->data);
	free(list.head);
}
void test_getOperator_should_give_operator_as_char_from_string(){
	int index = 2;
	void * data;
	expression = "12+";
	list = create_List();
	checkOperator(&index, expression, &list);
	getOperator(expression,list.head);
	assertEqual(*(char*)list.head->data,'+');
	free(list.head->data);
	free(list.head);
}

void test_createRPNList_should_create_list_of_numbers_and_operators_separately(){
	RPNList * resultList;
	expression = "123+";
	resultList = createRPNList(expression);
	assertEqual(*(int*)(resultList->head->data), 123);
	assertEqual(*(char*)resultList->tail->data, '+');
}

void test_createRPNList_should_create_list_of_numbers_and_multiple_operators(){
	RPNList * resultList;
	expression = "2 33 12345 + -";
	resultList = createRPNList(expression);
	assertEqual(*(int*)(resultList->head->data), 2);
	assertEqual(*(int*)resultList->head->next->data, 33);
	assertEqual(*(int*)resultList->head->next->next->data, 12345);
	assertEqual(*(char*)resultList->head->next->next->next->data,'+');
	assertEqual(*(char*)resultList->tail->data, '-');
	free(resultList->head->data);
	free(resultList->head->next->data);
	free(resultList->head->next->next->data);
	free(resultList->head->next->next->next->data);
	free(resultList->head);
	free(resultList->head->next);
	free(resultList->head->next->next);
	free(resultList->head->next->next->next);
	free(resultList);
}

void test_evaluate_should_add_two_numbers_2_and_3_in_Reverse_Polish_notation(){
	expression = "2 3 +";
	result = evaluate(expression);
	assertEqual(result, 5);
}

void test_evaluate_should_subtract_two_numbers_2_and_3_in_Reverse_Polish_notation(){
	expression = "2 3 -";
	result = evaluate(expression);
	assertEqual(result, -1);
}

void test_evaluate_should_multiply_two_numbers_2_and_3_in_Reverse_Polish_notation(){
	expression = "2 3 *";
	result = evaluate(expression);
	assertEqual(result, 6);
}

void test_evaluate_should_divide_two_numbers_2_and_3_in_Reverse_Polish_notation(){
	expression = "2 3 /";
	result = evaluate(expression);
	assertEqual(result, 0);
}

void test_evaluate_should_divide_two_numbers_6_and_2_in_Reverse_Polish_notation(){
	expression = "6 2 /";
	result = evaluate(expression);
	assertEqual(result, 3);
}

void test_evalute_should_give_20_for_11_plus_9(){
	expression = "11 9 +";
	result = evaluate(expression);
	assertEqual(result, 20);
}

void test_evaluate_should_work_for_multiple_numbers_and_operators_in_Reverse_Polish_notation(){
	expression = "2 3 4 + -";
	result = evaluate(expression);
	assertEqual(result, -5);
}

void test_evaluate_should_multiply_numbers_1_2_3_4_5_in_Reverse_Polish_notation(){
	expression = "1 2 3 4 5 * * * *";
	result = evaluate(expression);
	assertEqual(result, 120);
}

void test_evaluate_should_give_7_for_expression_2_2_2_multiply_2_minus_3_plus_plus(){
	expression = "2 2 2 * 2 - 3 + +";
	result = evaluate(expression);
	assertEqual(result, 7);
}

void test_evaluate_should_give_14_for_expression_5_1_2_plus_4_multiply_plus_3_minus(){
	expression = "5 1 2 + 4 * + 3 -";
	result = evaluate(expression);
	assertEqual(result, 14);
}

void test_evaluate_should_give_20_for_expression_2_2_2_2_2_multiply_multiply_2_plus_plus_2_minus_multiply(){
	expression = "2 2 2 2 2 * * 2 + + 2 - *";
	result = evaluate(expression);
	assertEqual(result, 20);
} 

// void test_evaluate_should_give_0_for_expression_2_2_minus_2_2_2_multiply_2_minus_minus_minus(){
// 	expression = "2 2 - 2 2 2 * 2 - - -";
// 	result = evaluate(expression);
// 	assertEqual(result, 0);
// }