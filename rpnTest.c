#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>

char *expression;
int result;

void test_checkOperator_should_return_1_for_valid_operator_for_RPN(){
	assertEqual(checkOpertaor('+'),1);
	assertEqual(checkOpertaor('-'),1);
	assertEqual(checkOpertaor('/'),1);
	assertEqual(checkOpertaor('*'),1);
}

void test_checkOperator_should_return_0_for_invalid_operator_for_RPN(){
	assertEqual(checkOpertaor('$'),0);
	assertEqual(checkOpertaor('A'),0);
	assertEqual(checkOpertaor('2'),0);
	assertEqual(checkOpertaor('%'),0);
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

void test_evaluate_should_give_20_for_expression_2_2_2_2_2_multiply_multiply_2_plus_plus_2_minus_multiply(){
	expression = "2 2 2 2 2 * * 2 + + 2 - *";
	result = evaluate(expression);
	assertEqual(result, 20);
} 

void test_evaluate_should_give_0_for_expression_2_2_minus_2_2_2_multiply_2_minus_minus_minus(){
	expression = "2 2 - 2 2 2 * 2 - - -";
	result = evaluate(expression);
	assertEqual(result, 0);
}

void test_evaluate_should_give_14_for_expression_5_1_2_plus_4_multiply_plus_3_minus(){
	expression = "5 1 2 + 4 * + 3 -";
	result = evaluate(expression);
	assertEqual(result, 14);
}