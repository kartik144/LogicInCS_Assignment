#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "t1.h"
#include "t5.h"

//Global Variables

char propositions[26];
int count=0;

/* This function counts the number of different propositional atoms in the logical formula(sees prefix form)*/

void prop_num()
{
    int i;
    int length = strlen(prefix);
    for(i=0;i<length;i++)
    {
        if(is_prop(prefix[i]))
        {
            propositions[prefix[i]-97] = 'y'; // Assigns 'y' to the corresponding position of a propositional atom if it occurs in the
                                            //logic formula.
        }
    }
    for(i=0;i<26;i++)
    {
        if(propositions[i]=='y')            //Counts the number of distinct logic formulas in prefix
        {
            count++;
        }
    }
}

/* This function updates the 'truth' variable of nodes which are propositional atoms in the tree
   constructed from the logical formula by seeing the global array 'propositions'*/

void prop_assign(Node* node)
{
    if(node==NULL)
    {
        return;
    }
    if(!is_prop(node->data))
    {
        prop_assign(node->left); //If not proposition, then call this function again on left and right sub_trees
        prop_assign(node->right);
    }
    else if(is_prop(node->data))
    {
        if(propositions[(node->data)-97]=='t') // If proposition and value in corresponding index of array is 't' then assign true.
        {
            node->truth = true;
        }
        else if (propositions[(node->data)-97]=='f')//Similar to above explanation for true.
        {
            node->truth = false;
        }
    }
}


/* The following function returns the truth value at the root node by recursively evaluating the
   truth values of the left sub_tree and the right sub_tree.This function uses recursive calls to the
   evaluations of left and right sub_trees.*/


bool evaluate(Node* node)
{
    if(is_prop(node->data))
    {
        return (node->truth);
    }
    else if(node->data=='+') // evaluates as (left_sub_tree||right_sub_tree)
    {
        node -> truth = (evaluate(node->left)||evaluate(node->right));
        return (node->truth);
    }
    else if(node->data == '~') // evaluates as !right_sub_tree
    {
        node->truth = !(evaluate(node->right));
        return (node->truth);
    }
    else if(node->data == '*') // evaluates node's truth as (left_sub_tree&&right_sub_tree)
    {
        node -> truth = (evaluate(node->left)&&evaluate(node->right));
        return (node -> truth);
    }
    else if (node->data == '>')  // (p > q) is evaluated as (~p+q)
    {
        node->truth = (!evaluate(node->left)||evaluate(node->right));
        return (node -> truth) ;
    }
}

/* This is the final function that returns the truth value of the entire logical formula. This function
calls the sub-functions that counts the number of distinct propositional atoms and evaluates truth values
at various nodes */

bool symbol_truth(Node* node)
{
    prop_num(); // Function call to get number of distinct propositional atoms. Updates in global variable count.

    int i;

    char t_value[count][2];

    printf("Please enter the propositional atom followed by a space, followed by its truth value:\n");

    for(i=0;i<count;i++)
    {
        scanf("\n%c %c",&t_value[i][0],&t_value[i][1]); // Takes input in the format "propositional_atom_alphabet truth value (as T or F)"
                                                       // (without quotes).
    }

    for(i=0;i<count;i++)
    {
        if(t_value[i][1]=='T')
        {
            propositions[(t_value[i][0])-97]='t';      // If the truth value corresponding to a propositional atom is 'T' update the corresponding
                                                      // position in the propositions array as 't' and 'f' if the truth value is false.
        }
        else if(t_value[i][1]=='F')
        {
            propositions[(t_value[i][0])-97]='f';
        }
    }

    prop_assign(node);   // Function call to assign the above received truth values to the atoms in the parse tree

    return evaluate(node); // Final function call to evaluate the truth values at parent nodes in a bottom - up fashion and return the truth value
                          // of the logic formula.
}


