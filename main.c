#include <stdio.h>
#include <string.h>
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"
#include "t5.h"
#include "t6.h"
#include "t7.h"
#include "t8.h"
int main()
{
	printf("Please Enter the infix expression:\n");
	gets(infix);
	char comp[1001];
	strcpy(comp,infix);
	infixToPrefix(infix);
	Node* cri = create_node(0);
	printf("Height of the non-cnf tree is %d\n",height_cal(cri));
    Node* cnff = cnf_form(cri);
    inorder(cnff);
    printf("\n");
	bool cnfff = validity(cnff);
	if(cnfff)
	{
		printf("The propositional formula is valid\n");
	}
	else 
	{
		printf("The propositional formula is not valid\n");
	}
	compare(comp);
	
	/*if(symbol_truth(temp))
		printf("True");
	else
		printf("False");
	getch();
	return 0;*/
}
