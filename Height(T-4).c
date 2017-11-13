#include <stdio.h>
#include <stdlib.h>
#include "t2.h"

/*This function calculates the height of the parse tree generated from the logic formula by recursively
calculating the heights of left sub_tree and right sub_tree and then adding one to the maximum of these heights.*/

int height_cal(Node* node)
{
    if(node!=NULL)
    {
       int left_height = height_cal(node->left); // Height of left sub_tree

       int right_height = height_cal(node->right); // Height of right sub_tree

       int height = 1 + (left_height>right_height?left_height:right_height); // Conditional operator for finding maximum of
                                                                             // height of left sub_tree and right sub_tree
       return height;
    }
    else

        return 0;
}

