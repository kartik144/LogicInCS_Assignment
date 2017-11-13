#ifndef T7_H_
#define T7_H_
bool is_literal(Node* literal);
bool is_atom(Node* atom);
bool validity(Node* cnf);
char pro[26];//Propositional array to keep track of occurrences of atoms and their negations.


#endif // T4_H_
