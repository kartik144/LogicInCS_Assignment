#ifndef T2_H_
#define T2_H_

#include <stdbool.h>

typedef struct node // The basic definition of node structure which forms the tree
{
   struct node *left,*right;  // Pointer to left and right sub_trees
   char data;      // Contains propositional atom or one of the operators('+','*','>','~')
   bool truth;     // Contains the truth value of node or propositional atom.
}Node;

Node* create_node(int start);
int end_tree; // Stores the value of the probable index of the corresponding right sub_tree in the prefix array.

#endif // T2_H_
