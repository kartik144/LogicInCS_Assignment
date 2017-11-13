#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"
#include "t5.h"
#include "t6.h"
#include "t7.h" //Contains the global variables of this file.
int number =0; // This is to keep track of when to empty the proposition array.
bool is_literal(Node* literal) // To update the status of the literal in the proposition array if the input node is a negation of atom.
{
	if(literal->data == '~') //Sees if there is negation
	{	
		if(pro[(literal->right->data)-97]=='y') //If already in the propositional array there is y means the atom and its negation have both occured
		{										//Then the function returns true.
			return true;						
		}
		else									//If there was no atom before, then updates the propositional array with 'n' which means that negation was encountered
		{
			pro[(literal->right->data)-97] = 'n';
		}
	}
	return false;
}
bool is_atom(Node* atom) //Similar to that of negation. Returns true if a negation of the atom considered was encountered, otherwise updates the array with 'y'.
{
	if(is_prop(atom->data))
	{	
		if(pro[(atom->data)-97] == 'n')
		{
			
			return true;
		}
		else
		{
			pro[(atom->data)-97] = 'y';
		}
	}
	return false;
}
bool validity(Node* cnf) //Main function which calls other functions and returns a boolean true if the cnf form input is valid else returns false.
{
	if(is_atom(cnf)) //Verification if node is atom and updation in propositional array if it is an atom.
	{				//If the is_atom function returns true, this also returns true,therefore formula becomes true, otherwise it is not evaluated.
		return true;
	}
	if(is_literal(cnf))//Verification if node is negation of atom and updation in propositional array if it is an negation of an atom.
	{					//If the is_literal function returns true, this also returns true,therefore formula becomes true, otherwise it is not evaluated.
		return true;
	}
	if(cnf->data=='*') // If the root node is '*' then empties the propositional array if + is encounter in evaluation of the left and right sub trees seperately.
	{
		bool left_eval,right_eval;
		number =0;
		left_eval = validity(cnf->left); // Evaluation of the left_sub tree
		number = 0;
		right_eval = validity(cnf->right); // Evaluation of right sub_tree
		if(left_eval && right_eval) // Returns true only if both the sub_trees are valid.
		{
			return true;
		}
		else
		{
			return false;
		} 		
	} 
	if(cnf->data == '+') // If the root node is '+' empties the propositional array only for the first time which is kept in track by the variable number.
	{		
		int i;
		if(number==0) //Emptying array.
		{
			for(i=0;i<26;i++)
			{
				pro[i] = ' ';
			}
			number+=1;
		}
		if(validity(cnf->left)|| validity(cnf->right)) //If atlease one sub_tree which has '+' returns true, this function returns true
		{
			return true;
		}
	}
	return false;	//If true is not returned anywhere else in the function, it means the function is not valid and returns false.
}