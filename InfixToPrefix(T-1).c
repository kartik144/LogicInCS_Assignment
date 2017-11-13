#include <string.h>
#include "t1.h"
#include <stdio.h>

// Symbols used and their meaning: ~ NOT,+ OR, * AND, > IMPLIES

char stack[1000];   // Stack to store all the operands and brackets
char infix[1001];   // Global variable to store the input infix propositional logic formula
char prefix[1001]; // Global variable to store the output prefix propositional logic formula
int top=-1;         // variable to point to the top of the stack

//--------function declarations---------
void reverse(char *s);
char pop();
void push(char e);
int checkSymbol(char ch);
void infixToPrefix(char *s);
//--------------------------------------

void reverse(char *s)   // function to reverse the string passed
{
    int i,j=0;
    char temp;
    for(i=strlen(s)-1;i>j;i--,j++)
    {
        temp=s[j];
        s[j]=s[i];
        s[i]=temp;
    }
}
char pop()      // function to delete an element from the top of the stack and return it
{
    if(top==-1)
        return '\0';
    else
    {
        return stack[top--];
    }


}

void push(char ch)      // function to push an element into the stack
{
    if(top!=999)
    {
        stack[++top]=ch;
    }

    return;
}

int checkSymbol(char ch)    // function that returns 0 if the passed character is an atom otherwise returns a number between
{                           // 1 to 6 according to its precedence order (IMPLIES>OR>AND>NOT>Brackets)
    if((ch>='a' && ch<='z'))
        return 0;
    else
    {
        switch(ch)
        {
            case '(': return 6;
            case ')': return 5;//The precedence order of brackets is reversed as the string is also reversed
            case '~': return 4;
            case '*': return 3;
            case '+': return 2;
            case '>': return 1;
        }
    }

        return -999;
}

void infixToPrefix(char* s) // Function to convert the given infix propositional logic formula to prefix
{
   
    reverse(s);//Reverses the given input in infix notation

    int i,j=0,k=0;
    for(i=0;i<strlen(s);i++)    // Scans each element in the reversed string
    {
        k=checkSymbol(s[i]);
        if(k==0) //Checking if character at i is an atom.
        {
            prefix[j]=s[i];
            j++;
        }
        else if(k==4) // Checking if character at i is NOT(~)
        {
            if(checkSymbol(s[i+1])==5)
            {
                push(s[i]);
            }
            else
            {
                prefix[j]=s[i];
                j++;
            }

        }
        else if(k==5) //Checking if character at i is an open bracket
        {
            push(s[i]);
        }
        else if(k==6) //Checking if character at i is a closed bracket
        {
            char ch=pop();
            while(checkSymbol(ch)!=5)
            {
                prefix[j]=ch;
                j++;
                ch=pop();
            }// If it is a closed bracket then pop elements from stack until an open bracket is encountered in stack
        }
        else // Checking if character at i is AND/OR/IMPLIES
        {
            if(top>=0 && (checkSymbol(s[i])<checkSymbol(stack[top])) && checkSymbol(stack[top])!=5)//to check the precedence order of character with top
            {                                                                                      // element at the stack
                prefix[j]=pop();
                j++;
                push(s[i]);
            }
            else
            {
                push(s[i]);
            }
        }
    }

    while(top!=-1)
    {
        prefix[j]=pop();
        j++;
    }                       // to empty the stack of its remaining elements
    prefix[j] = '\0';

    reverse(prefix);// reverses the obtained postfix string to make it prefix
}

