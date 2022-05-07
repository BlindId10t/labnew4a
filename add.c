#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "add.h"


void write (char* msgs, int i) {
    while (i > 0) {
        printf("%s", msgs);
        i--;
    }
}

void show_tree(Node* p, int indent) {
    if(p != NULL) {
        if(p->right) {
            show_tree(p->right, indent + 4); //indent - отступ; сначала выводим
        }
        if (indent) {
            write(" ", indent); //если отступ не 0
        }
        if (p->right) { //если есть правое поддерево, то подготовь для него ветку
            puts(" /");
            write(" ", indent);
        }
        printf("%d\n ", p->info);
        if(p->left) {
            write(" ", indent);
            printf(" \\\n"); // если есть левое поддерево, то вот его ветка
            show_tree(p->left, indent + 4);
        }
    }
}

char * my_readline() {
    char buf[81] = {0}; //buffer for reading 80 symbols, last for zero-terminator
    int n = 0;
    char *res = NULL;
    int len = 0;
    do {
        n = scanf("%80[^\n]", buf); //read symbols to buffer; n = 1 if stdin not emty, n = 0 if emty and n = -1 if EOF (80 it's maximum per scanf call)
        //if in stding over 80 symbols, they they are reading for a few scanf calls in do while cycle
        if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char *) realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len + 1); //copy part of input from buffer to result string; + 1 for zero-terminator
            len = str_len;
        }
        else if (n == 0 && !res) {
            res = (char*) calloc(1, sizeof(char)); //empty string, only zero-terminator
            scanf("%*c"); //read \n after pressing enter
        }
        else scanf("%*c"); //read \n after pressing enter
    } while(n > 0);
    return res;
}

int getIntFile (int* a, FILE * Fin) {
    int n;
    do {
        n = fscanf(Fin, "%d", a);
        fscanf(Fin, "%*[^\n]");
        if (n < 0)
            return 0;
        if (n == 0 || a < 0) {
            fscanf(Fin, "%*c");
        }
    } while (n == 0);
    return 1;
}

int digit_num(int n) {
    if (n == 0)
        return 1;
    if (n < 0)
        n = -n;
    int sum = 0;
    while (n > 0) {
        n /= 10;
        sum += 1;
    }
    return sum;
}

void graph(FILE* fd, Node* ptr) {
    if (ptr != NULL) {
        if (ptr->left != NULL) {
            int num = digit_num(ptr->key); //кол-во знаков
            char* str = (char*)malloc((num+1)*sizeof(char));
            sprintf(str, "%d", ptr->key); //как printf, но вывод в массив str
            fwrite("\n", sizeof(char), 1, fd);
            fwrite(str, sizeof(char), num, fd);
            fwrite("->", sizeof(char), 2, fd);
            num = digit_num(ptr->left->key);
            str = (char*)realloc(str, sizeof(char) * (num + 1));
            sprintf(str, "%d", ptr->left->key);
            fwrite(str, sizeof(char), num, fd);
            free(str);
        }
        if (ptr->right != NULL) { //то же самое, но с right
            int num = digit_num(ptr->key);
            char* str = (char*)malloc((num+1)*sizeof(char));
            sprintf(str, "%d", ptr->key);
            fwrite("\n", sizeof(char), 1, fd);
            fwrite(str, sizeof(char), num, fd);
            fwrite("->", sizeof(char), 2, fd);
            num = digit_num(ptr->right->key);
            str = (char*)realloc(str, sizeof(char) * (num + 1));
            sprintf(str, "%d", ptr->right->key);
            fwrite(str, sizeof(char), num, fd);
            free(str);
        }
        /*if ((ptr->left == NULL) && (ptr->right == NULL)) {
            int num = digit_num(ptr->key);
            char* str = (char*)malloc((num+1)*sizeof(char));
            sprintf(str, "%d", ptr->key);
            fwrite("\n", sizeof(char), 1, fd);
            fwrite(str, sizeof(char), num, fd);
            free(str);
        }*/
        graph(fd, ptr->left);
        graph(fd, ptr->right);
    }
}