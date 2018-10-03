#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "tree.h"

void tree_transform(Tree t, char c, Tree expr);
int variable_match(Tree t, char c);
int variable_is_in_tree(Tree t, char c);

#endif
