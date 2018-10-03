#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"
#define TOKEN_SIZE 100

int main(void)
{
    //system("chcp 65001");

    Token tokens[TOKEN_SIZE];
    int tokens_qty = 0;
    Tree tree;

    int working = 1;
    char input;
    do {
        printf("Введите команду (? - справка)\n");
        scanf(" %c", &input);
        switch (input) {
            case '?':
            case 'h':
                printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
                printf("a    Ввести выражение\n");
                printf("p    Печать выражения\n");
                printf("t  	 Печать дерева\n");
                printf("c  	 Выполнить задание\n");
                printf("?  	 Справка\n");
                printf("q  	 Выход\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                break;
            case 'a': //add

                printf("Введите выражение:\n");
                getchar();
                Token token;
                token_next(&token);
                tokens_qty = 0;
                while (token.type != FINAL) {
                    tokens[tokens_qty++] = token;
                    token_next(&token);
                }
                tree = tree_create(tokens, 0, tokens_qty - 1);
                break;
            case 'p': //linear
                if(tokens_qty == 0) {
                    printf("Выражение не введено, печать невозможна\n");
                    return 1;
                }
                else {
                    printf("\nВыражение в линейном представлении:\n");
                    tree_infix(tree);
                    printf("\n");
                }
                break;
            case 't': //tree
                if(tokens_qty == 0) {
                    printf("Выражение не введено, печать невозможна\n");
                    return 1;
                }
                else {
                    printf("\nДерево выражения:\n");
                    tree_print(tree, 0);
                }
                break;
            case 'c': //task
                if(tokens_qty == 0) {
                    printf("Выражение не введено, преобразование невозможно\n");
                    return 1;
                }
                else {
                    tree_transform(&tree);
                    printf("Преобразование выполнено\n");
                    tree_print(tree,0);
                }
                break;

            case 'q':
                printf("Программа завершена\n");
                working = 0;
                break;
            default:
                printf("Неизвестная команда\n");
                break;
        }
    }
    while(working);














    /*for (int i = tokens_qty-1; i-2 >= 0; --i) {
        if(tokens[i].type == INTEGER && tokens[i-1].type == OPERATOR && tokens[i-1].data.operator_name == '*'
           && tokens[i-2].type == VARIABLE) {
            char c = tokens[i-2].data.variable_name;
            int num = tokens[i].data.value_int;
            tokens[i-2].type = INTEGER;
            tokens[i-2].data.value_int = num;
            tokens[i].type = VARIABLE;
            tokens[i].data.variable_name = c;
        }
    }

    tree = tree_create(tokens, 0, tokens_qty - 1);



    printf("\nДерево выражения после преобразования:\n");
    tree_print(tree, 0);*/



    return 0;
}

