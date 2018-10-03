#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ctype.h>
#include "lexer.h"
#include "tree.h"
#include "transform.h"

int main(void)
{   
    Token tokens[TOKEN_SIZE];
    int ind = 0;
    printf("Введите выражение:\n");
    Token token;
    token_next(&token);

    while (token.type != FINAL) {
        tokens[ind++] = token;
        token_next(&token);
    }

    if(ind == 0) {
        printf("Выражение не введено, преобразование невозможно\n");
        exit(ERROR_INPUT);
    }
    printf("Введите добавляемое выражение:\n");

    Token exprs[TOKEN_SIZE];
    int ind_expr = 0;

    Token expr;
    token_next(&expr);

    while(expr.type != FINAL) {
        exprs[ind_expr++] = expr;
        token_next(&expr);
    }

    if(ind_expr == 0) {
        printf("Добавляемое выражение не введено, замена невозможна.\n");
        exit(ERROR_INPUT);
    }

    printf("\nВыражение в линейном представлении:\n");
    for (int i = 0; i < ind; ++i) {
        token_print(&tokens[i]);
    }

    printf("\nДобавляемое выражение в линейном представлении:\n");
    for (int i = 0; i < ind_expr; ++i) {
        token_print(&exprs[i]);
    }

    printf("\nДерево выражения до преобразования:\n");
    Tree tree;
    tree = tree_create(&tokens[0], 0, ind - 1);
    tree_print(tree, 0);
    printf("\nДерево добавляемого выражения:\n");
    Tree tree_expr;
    tree_expr=tree_create(&exprs[0],0,ind_expr-1);
    tree_print(tree_expr,0);
    char var;
    printf("\nВведите переменную, которую нужно заменить на выражение:\n");
    scanf("%c", &var);
    if(!variable_is_in_tree(tree, var)) {
        printf("Этой переменной нет в выражении...\n");
        exit(ERROR_INPUT);
    } else {
        tree_transform(tree, var, tree_expr);
    }
    printf("\nДерево выражения после преобразования:\n");
    tree_print(tree, 0);

    printf("\nВыражение в линейном представлении:\n");
    tree_infix(tree);
    printf("\n");
    tree_destroy(&tree);
    return 0;
}
