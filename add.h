#pragma once
#include "tree.h"
#ifndef sew
void show_tree (Node* ptr, int indent);
char * my_readline();
int getIntFile (int* a, FILE * Fin);
Node* free_tree(Node* ptr);
int digit_num(int n);
void graph(FILE* fd, Node* ptr);
#endif

