#pragma once
#include "tree.h"

int getInt (int* a);
Node* insert(Tree* tree, int key, int info, int* flag);
Node* FindByKey(Node* root, int key);
Node* delete_node(Node* root, int key);
void free_stack(Stack* stack);
void printStackValue(Node* value);
void show_stack(Stack stack, void (*printStackValue)(Node*));
Stack find_spec(Node* root, int key, Stack* stack);
void traversal(Node* root, int left_b, int right_b, int flag);

