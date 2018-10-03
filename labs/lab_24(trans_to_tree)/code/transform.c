#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "tree.h"
#include "transform.h"

void token_next(Token *t) {
	static bool can_be_unary = true; 
	char c;

	do { // Избавление от пробельных литер
		c = fgetc(stdin);
	} while (c == ' ');

	if (c == EOF || c == '\n') { // The end
		t->type = FINAL;
	}

	else if (isalpha(c) || c == '_') { // Переменные
		t->type = VARIABLE;
		t->data.variable_name = c;
		can_be_unary = false;
	}

	else if (isdigit(c)) { // Числа
		float result;
		ungetc(c, stdin);
		scanf("%f", &result);

		if (result == (int) result) {
			t->type = INTEGER;
			t->data.value_int = (int) result;
		} else {
			t->type = FLOATING;
			t->data.value_float = result;
		}
		can_be_unary = false;
	}

	else if (c == '(' || c == ')') {
		t->type = BRACKET;
		t->data.is_left_bracket = (c == '(');
		can_be_unary = t->data.is_left_bracket;
	}

	else if (can_be_unary && (c == '-' || c == '+')) { // Учёт минуса перед числом
		int m = (c == '+') ? +1 : -1; // Знак

		do {
			c = fgetc(stdin);
		} while (isspace(c));

		if (isdigit(c)) {
			ungetc(c, stdin);
			token_next(t); // После минуса и т.д. надо число считать
			if (t->type == INTEGER) {
				t->data.value_int = m * (t->data.value_int);
			} else {
				t->data.value_float = m * (t->data.value_float);
			}
		} else {
			ungetc(c, stdin);
			t->type = OPERATOR;
			t->data.operator_name = '-';
			can_be_unary = true;
		}
	}

	else {
		t->type = OPERATOR;
		t->data.operator_name = c;
		can_be_unary = true;
	}
}

void token_print(Token *t) {
	switch (t->type) {
	case FINAL:
		break;
	case INTEGER:
		printf("%d", t->data.value_int);
		break;
	case FLOATING:
		printf("%lg", t->data.value_float);
		break;
	case VARIABLE:
		printf("%c", t->data.variable_name);
		break;
	case OPERATOR:
		printf("%c", t->data.operator_name);
		break;
	case BRACKET:
		printf("%c", (t->data.is_left_bracket) ? '(' : ')');
		break;
	}
}

int variable_match(Tree t, char c) {
	return (t != NULL) && (t->node.type == VARIABLE)
			&& (t->node.data.variable_name == c);
}

void tree_transform(Tree t, char c, Tree expr) {
	if (t != NULL) {
		tree_transform(t->left, c, expr);
		tree_transform(t->right, c, expr);

		if (t->right) {
			if (variable_match(t->right, c)) {
				free(t->right);
				t->right = expr;
			}
		}
		if (t->left) {
			if (variable_match(t->left, c)) {
				free(t->left);
				t->left = expr;
			}
		}
	}
}

int variable_is_in_tree(Tree t, char c) {
	if (!t)
		return 0;
	if (variable_match(t, c))
		return 1;
	if (!variable_is_in_tree(t->left, c))
		return variable_is_in_tree(t->right, c);
	else
		return 1;
}
