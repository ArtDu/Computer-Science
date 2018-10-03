#include <math.h>
#include "tree.h"
#include "transform.h"
#include "lexer.h"


int transform_ints(Tree *t);

int match_int(Tree *t) {
    if((*t)->node.type == OPERATOR && ((*t) != NULL) && ((*t)->node.data.operator_name == '*')) {

        return match_int(&((*t)->right))+match_int(&((*t)->left));

    }
    else if((*t)->node.type == INTEGER) {
        return 1;
    }
    else {
        return 0;
    }
}

int match_var(Tree *t) {
    if((*t)->node.type == OPERATOR && ((*t) != NULL) && ((*t)->node.data.operator_name == '*')) {

        return match_var(&((*t)->right))+match_var(&((*t)->left));

    }
    else if((*t)->node.type == VARIABLE) {
        return 1;
    }
    else {
        return 0;
    }
}

int match_power_nums(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '*')
           &&
           (
            (
                (match_int(&((*t)->right)))>0
                &&
                (match_var(&((*t)->left)))>0
            )
              ||
            (
                (match_int(&((*t)->left)))>0
                &&
                (match_var(&((*t)->right)))>0
            )
           );
}

int match_power_mult(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '*')
           && (
                   (
                           ((*t)->left->node.type == INTEGER)
                           &&
                           ((*t)->right->node.type == VARIABLE)
                   )
                   ||
                   (
                           ((*t)->left->node.type == VARIABLE)
                           &&
                           ((*t)->right->node.type == INTEGER)
                   )
           );
}

void multi_to_sum(Tree *main_t, int num, char c){
    if(num>0) {

        Tree tmp;
        (*main_t)->node.type = OPERATOR;
        (*main_t)->node.data.operator_name = '+';
        tmp = (Tree) malloc(sizeof(struct tree_node));
        tmp->right = NULL;
        tmp->left = NULL;
        (*main_t)->left = tmp;
        (*main_t)->left->node.type = VARIABLE;
        (*main_t)->left->node.data.variable_name = c;
        num--;
        if (num == 1) {
            tmp = (Tree) malloc(sizeof(struct tree_node));
            tmp->right = NULL;
            tmp->left = NULL;
            (*main_t)->right = tmp;
            (*main_t)->right->node.type = VARIABLE;
            (*main_t)->right->node.data.variable_name = c;
            num -= 1;
        }
        else {
            tmp = (Tree) malloc(sizeof(struct tree_node));
            tmp->right = NULL;
            tmp->left = NULL;
            (*main_t)->right = tmp;
            multi_to_sum(&((*main_t)->right),num,c);
        }
    }

}


void transform_power(Tree *t)
{
    int num = 0;
    char c;
    Tree main_t;
    if((*t)->left->node.type == VARIABLE) {
        c = (*t)->left->node.data.variable_name;
        num = (*t)->right->node.data.value_int;
        
    }
    else if((*t)->right->node.type == VARIABLE) {
        c = (*t)->right->node.data.variable_name;
        num = (*t)->left->node.data.value_int;
    }


    if(num == 0) {
        main_t = (Tree) malloc(sizeof(struct tree_node));
        main_t->node.type = INTEGER;
        main_t->node.data.value_int = 0;

        main_t->left  = NULL;
        main_t->right = NULL;

        
    }
    else {
        main_t = (Tree) malloc(sizeof(struct tree_node));
        main_t->left  = NULL;
        main_t->right = NULL;
        multi_to_sum(&main_t,num,c);
    }
    
    //tree_delete(t);
    *t = main_t;


}

void tree_transform_nums(Tree *t)
{
    if ((*t) != NULL) {

        if (match_power_nums(t)) {

            while(transform_ints(t));

            //transform_power(t);
        }

        tree_transform_nums(&((*t)->left));
        tree_transform_nums(&((*t)->right));
    }
}

void tree_transform_mult(Tree *t) {
    if ((*t) != NULL) {

        if (match_power_mult(t)) {
            transform_power(t);
        }
        tree_transform_mult(&((*t)->left));
        tree_transform_mult(&((*t)->right));
    }
}

void tree_transform(Tree *t)
{
    if ((*t) != NULL) {

        tree_transform_nums(t);
        tree_transform_mult(t);
    }
}

int transform_ints(Tree *t) {
    Tree tmp_t;
    tmp_t = (Tree) malloc(sizeof(struct tree_node));
    tmp_t->right = NULL;
    tmp_t->left = NULL;
    if((*t)->node.type == OPERATOR && ((*t) != NULL) && ((*t)->node.data.operator_name == '*')) {

        if((*t)->right->node.type == INTEGER && (*t)->left->node.type == OPERATOR
           && (*t)->left->node.data.operator_name == '*')
        {
            if((*t)->left->right->node.type == VARIABLE) {
                tmp_t = (*t)->right;
                (*t)->right = (*t)->left->right;
                (*t)->left->right = tmp_t;
            }
            else if((*t)->left->right->node.type == INTEGER) {
                (*t)->left->right->node.data.value_int *= (*t)->right->node.data.value_int;
                *t = ((*t)->left);
                return 1;
            }
            else if((*t)->left->left->node.type == VARIABLE) {
                tmp_t = (*t)->right;
                (*t)->right = (*t)->left->left;
                (*t)->left->left = tmp_t;
            }
            else if((*t)->left->left->node.type == INTEGER) {
                (*t)->left->left->node.data.value_int *= (*t)->right->node.data.value_int;
                *t = ((*t)->left);
                return 1;
            }

        }
        else if((*t)->left->node.type == INTEGER && (*t)->right->node.type == OPERATOR
                && (*t)->right->node.data.operator_name == '*') {
            if((*t)->right->left->node.type == VARIABLE) {
                tmp_t = (*t)->left;
                (*t)->left = (*t)->right->left;
                (*t)->right->left = tmp_t;
            }
            else if((*t)->right->left->node.type == INTEGER) {
                (*t)->right->left->node.data.value_int *= (*t)->left->node.data.value_int;
                *t = ((*t)->right);
                return 1;
            }
            else if((*t)->right->right->node.type == VARIABLE) {
                tmp_t = (*t)->left;
                (*t)->left = (*t)->right->right;
                (*t)->right->right = tmp_t;
            }
            else if((*t)->right->right->node.type == INTEGER) {
                (*t)->right->right->node.data.value_int *= (*t)->left->node.data.value_int;
                *t = ((*t)->right);
                return 1;
            }

        }

    }
    return 0;
}