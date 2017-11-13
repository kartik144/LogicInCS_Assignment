#ifndef T6_H_
#define T6_H_
Node* cnf_form(Node* parse_tree);
Node* impl_free(Node* impl);
Node* nnf(Node* neg);
Node* distr(Node* left_node,Node* right_node);
Node* cnf(Node* form);
#endif
