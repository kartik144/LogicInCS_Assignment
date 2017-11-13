#include <stdio.h>
#include <string.h>
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t6.h"
int size(Node* input) // Calculates the size of a given tree i.e the number of nodes in it.
{
if(input==NULL)
{
	return 0; // If pointer is null, it is not a node.Therfore, returns 0.
}
else
{
	return 1+size(input->left)+size(input->right); // In all other cases, returns 1 + size of left node and size of right node
}											
}
void compare(char *s) // Takes an infix expression as input
{
	infixToPrefix(s); // Gives a prefix expression. This is updated in the global prefix array in t2.h
	end_tree = 0; // If in the main file, several tree creations are done, then for each tree creation end_tree must start with zero.
	Node* tree = create_node(0); // Tree creation for the input infix expression
	int size_tree = size(tree); //Calculates size of the tree of the input infix expression
    tree = cnf(nnf(impl_free(tree)));//returns the cnf of the earlier tree
	int size_cnf = size(tree); // Calculates the size of the cnf logical formula
	printf("Size of tree is %d\n",size_tree);
	printf("Size of cnf form is %d\n",size_cnf);
	double ratio = (double)size_cnf/size_tree;
	printf("The size of cnf formula is %.3lf times of that of the size of input logical formula",ratio);
}