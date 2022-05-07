#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "base.h"
#include "add.h"
#include "time.h"

int T_Add (Tree* tree) {
    int key = rand()%(amount*100) + 1;
    int info = rand()%(amount*100) + 1;
    int flag = 0;
    Node* rc = insert(tree, key, info, &flag);
    if (flag == 1) {
        return 0;
    }
    return 1;
}

int T_keyFind (Tree* tree) {
    int key = rand()%(amount*100) + 1;
    Node* rc = FindByKey(tree->root, key);
    if (rc == 0)
        return 0;
    return 1;
}

int T_Delete (Tree* tree) {
    int key = rand()%(amount*100) + 1;
    Node* rc = delete_node(tree->root, key);
    if (rc == 0)
        return 0;
    return 1;
}

int T_specFind (Tree* tree) {
    int key = rand()%(amount*100) + 1;
    Stack stack;
    stack.size = 0;
    stack = find_spec(tree->root, key, &stack);
    if (stack.size == 0)
        return 0;
    return 1;
}

int T_Traversal (Tree* tree) {
    int left_border = rand()%(amount*100) + 1;
    int right_border = rand()%(amount*100) + 1;
    int flag = 1;
    traversal(tree->root, left_border, right_border, flag);
    return 1;
}

Tree* rand_data(Tree* tree, int i) {
    for (int j = 0; j < i; j+=1) {
        if (T_Add(tree) == 0)
            j -= 1;
    }
    return tree;
}
