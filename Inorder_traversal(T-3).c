#include <stdio.h>
#include "t3.h"
#include "t1.h"
#include "t2.h"
/* This function traverses the tree generated from the logic formula in a way called as in-order traversal.
In-order traversal first prints the left sub_tree , then root and then the right sub_tree.*/

void inorder(Node* node)
{
    if(node!=NULL)  // Checks if the node is not NULL
    {
        if(node->left!=NULL&&node->right!=NULL)
        {
           printf("(");      // Adding left bracket for all cases except when node is a negation
        }                   // or when node is a propositonal atom.

        inorder(node->left); // In-order traversal of left node.

        printf("%c",node->data); // Print the root of that sub_tree

        inorder(node->right); // In-order traversal of the right node.

        if(node->left!=NULL&&node->right!=NULL)
        {
           printf(")");                          // Same as left bracket.
        }
    }
    else
        return;
}
