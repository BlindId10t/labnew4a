#pragma once

#define STACK_MAX_SIZE 100
#define amount 100000
//#define sew

typedef struct Tree {
    struct Node* root;
} Tree;

typedef struct Stack {
    struct Node* data[STACK_MAX_SIZE];
    int size;
} Stack;

#ifndef sew
typedef struct Node {
    int key;
    int info;
    struct Node * left;
    struct Node * right;
} Node;
#endif

#ifdef sew
typedef struct Node {
    int key;
    int info;
    int thread; //флаг, показывающий является ли link[1] настоящей связью (значение 1), или только промежуточной (значение 0)
    struct Node * left;
    struct Node * right;
    struct Node* link[2]; //link[0] <=> left, мб потом уберу, link[1] <=> next
} Node;

Node* make_node(int key, int info);
#endif


/*
int dialog(const char* msgs[], int N);
int D_Add (Tree* tree);
int D_keyFind (Tree* tree);
int D_Delete (Tree* tree);
int D_specFind(Tree* tree);
int D_Traversal(Tree* tree);
int D_treeShow(Tree* tree);
int D_Download(Tree* tree);
int D_Freq(Tree* tree);
int D_Graphviz(Tree* tree);

int T_Add (Tree* tree);
int T_keyFind (Tree* tree);
int T_Delete (Tree* tree);
int T_specFind(Tree* tree);
int T_Traversal(Tree* tree);
Tree* rand_data(Tree* tree, int i);
int D_Time(Tree* tree);

int getInt (int* a);
Node* insert(Tree* tree, int key, int info, int* flag);
Node* FindByKey(Node* root, int key);
Node* delete_node(Node* root, int key);
void printStackValue(Node* value);
void show_stack(Stack stack, void (*printStackValue)(Node*));
Stack find_spec(Node* root, int key, Stack* stack);
Node* traversal(Node* root, int left_b, int right_b, int flag);


void show_tree (Node* ptr, int indent);
char * my_readline();
int getIntFile (int* a, FILE * Fin);
Node* free_tree(Node* ptr);
int digit_num(int n);
void graph(FILE* fd, Node* ptr);*/


/*Вопросики
 * 1. Правильный ли обход, симметричный и прямой обход
 *  1.1. СПРОСИТЬ МОЖНО ЛИ изменить структуру и добавить тэги прошивки ltag и rtag https://libeldoc.bsuir.by/bitstream/123456789/799/2/Serebryanaya_strukt.pdf
 * 2. Правильный ли специальный поиск
 * 3. Почему не открывается файл
 * 4. Почему не работает графвиз
*/

