#include <stdio.h>
#include <stdlib.h>
#include "t2.h"
#include "t3.h"
Node* impl_free(Node* impl) // Gives the implication free form of the input formula
{
	if(impl==NULL||(impl->left ==NULL && impl->right ==NULL)) // If the node is a literal this is executed.
	{
		return impl;
	}
	if (impl->data =='>') // If implication is the root node. returns ~(left_node)+(right_node)
	{
		impl->data = '+';
		Node* add = (Node*)malloc(sizeof(Node)); //Creates a new node
		add -> data = '~'; // Because ~p+q
		add->left = NULL;
		add-> right = impl->left; // Attaches the left of the input node to the right of the new node as there is '~'.
		impl->left = add;
	}
	impl_free(impl->left); // Recursive calls to left and right sub_trees
	impl_free(impl->right);
	return impl;
}
Node* nnf(Node* neg) // Returns the tree which is the negation normal form of a tree. Requires formula to be implication free.
{
	if(neg==NULL) 
	{
		return NULL;
	}
	if(neg->data=='~') // Executed when root node is '~'. Three cases arise. First ~~ and other ~p*q and ~p+q
	{
		if(neg->right->data=='~') //When ~~ is present remove the both ~. Therefore the right sub_tree of second ~ replaces earlier ~~
		{
			neg = neg->right->right;
			return nnf(neg); // Returns nnf of this modified tree. This is to consider the case of ~~~~p
		}
		else if(neg->right->data=='+'||neg->right->data=='*') //If root node is '+' or '*', the root node is to be reversed and negations have to be			
		{													//added to left and right sub_trees.
			Node* add_left = (Node*)malloc(sizeof(Node)); //New nodes to add negation.
			Node* add_right = (Node*)malloc(sizeof(Node));
			char c = neg->right->data;
			add_left->data = '~';
			add_right->data = '~';
			add_left->left = NULL;
			add_right->left = NULL;
			add_left->right = neg->right->left; // Adding left and right sub trees to the new negations.
			add_right->right = neg->right->right;
			neg -> data = (c=='+')?'*':'+'; //Reversing the data of the input node.
			neg->left = add_left;
			neg->right = add_right;
		}
	}
	neg->left = nnf(neg->left); // NNf of the new left sub tree
	neg->right = nnf(neg->right); // NNF of the new right sub tree
	return neg;
}
Node* distr(Node* left_node,Node* right_node) //Distr function which is called by cnf function
{
	if(left_node->data=='*') //If node has '*', distribution of left and right subtrees are called with the other node which is passes as arguments.							
	{						// This is for left node and the next is for right node.
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = '*';
		new_node->left = distr(left_node->left,right_node);
		new_node->right = distr(left_node->right,right_node);
		return new_node;
	}
	else if(right_node->data=='*')
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = '*';
		new_node->left = distr(left_node,right_node->left);
		new_node->right = distr(left_node,right_node->right);
		return new_node;
	}
	else // If no '*' as root node, then returns the or of the two input nodes passed as argument.
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = '+';
		new_node->left = left_node;
		new_node->right = right_node;
		return new_node;
	}
}
Node* cnf(Node* form) // Gives the CNF of the input which is in NNF form and is implication free.
{
	if(form==NULL||form->left == NULL) // If node is a literal
	{
		return form;
	}
	if(form->data == '*') // If root node is '*' returns AND of cnf of the left and right sub trees.
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node -> data = '*';
		new_node->left = cnf(form->left);
		new_node->right = cnf(form->right);
		return new_node;
	}
	if(form->data == '+') // If node is '+', calls the distr function on the cnf forms of the left and right sub trees.
	{
		return distr(cnf(form->left),cnf(form->right));
	}
}
Node* cnf_form(Node* parse_tree) //This function is to be called in the main file. This calls the other required functions automatically.
{
	Node* cnf_formula = cnf(nnf(impl_free(parse_tree)));
	return cnf_formula;
}
