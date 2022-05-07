#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "base.h"
#include "add.h"
#include "time.h"

int dialog(const char* msgs[], int N) {
    char* errmsg = "";
    int rc, n;
    do {
        puts(errmsg);
        errmsg = "Error! Repeat...\n";
        for (int i = 0; i < N; i++)
            puts(msgs[i]);
        printf("\n");
        n = getInt(&rc);
        if (n == 0)
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}

int D_Add (Tree* tree) {
    puts("Enter key: --> ");
    int key;
    if (getInt(&key) == 0)
        return 0;
    puts("Enter info: --> ");
    int info;
    if (getInt(&info) == 0)
        return 0;
    int flag = 0;
    Node* rc = insert(tree, key, info, &flag);
    if (!rc)
        puts("Error!\n");
    else if (flag == 1) {
        puts("There is already that key in the tree!");
        printf("(which info is %d)\n", rc->info);
    }
    return 1;
}

int D_keyFind (Tree* tree) {
    puts("Enter key: --> ");
    int key;
    int n = getInt(&key);
    if (n == 0)
        return 0;
    Node* rc = FindByKey(tree->root, key);
    if (!rc)
        puts("Can not find anything!");
    else {
        printf("node's info: %d\n", rc->info);
    }
    return 1;
}

int D_Delete (Tree* tree) {
    puts("Enter key: --> ");
    int key;
    if (getInt(&key) == 0)
        return 0;
    Node* rc = delete_node(tree->root, key);
    if (!rc)
        puts("Can not delete anything!");
    else {
        tree->root = rc;
        puts("Deleting complete!");
        printf("(new root is a node with info %d)\n", rc->info);
    }
    return 1;
}

int D_specFind(Tree* tree) { //Поиск элемента с ключом, значение которого наиболее близко к заданному, но не совпадает с ним
    puts("Enter key: --> ");
    int key;
    if (getInt(&key) == 0)
        return 0;
    Stack stack;
    stack.size = 0;
    stack = find_spec(tree->root, key, &stack);
    if (stack.size == 0)
        puts("Can not find anything!");
    else {
        show_stack(stack, printStackValue);
        free_stack(&stack);
    }
    return 1;
}

int D_Traversal(Tree* tree) {
    int left_border, right_border;
    do {
        puts("Enter left border: --> ");
        if (getInt(&left_border) == 0)
            return 0;
        puts("Enter right border: -->");
        if (getInt(&right_border) == 0)
            return 0;
    } while (left_border > right_border);
    puts("\ntree traversal pre-order:");
    int flag = 0;
    traversal(tree->root, left_border, right_border, flag);
    puts("");
    return 1;
}

int D_treeShow(Tree* tree) {
    //show_tree(tree->root);
    puts("");
    show_tree(tree->root, 0);
    puts("");
    return 1;
}

int D_Download(Tree* tree) {
    printf("Input name of file\n");
    scanf("%*c");
    char *file_name = my_readline();
    FILE *Fin = fopen(file_name, "r");
    if (!Fin) {
        printf("Error! Can not open file! Breaking!\n");
        return 1;
    }
    int key, info, n1 = 1, n2 = 2;
    do {
        if (n1 && n2) {
            int age;
            int n1 = getIntFile(&key, Fin);
            int n2 = getIntFile(&info, Fin);
        }
        int flag = 0;
        if (n1 && n2) insert(tree, key, info, &flag);
    } while (n1 && n2);
    fclose(Fin);
    free(file_name);
    return 1;
}

int D_Freq(Tree* tree) {
    return 1;
}

int D_Graphviz(Tree* tree) { //all methods from https://www.youtube.com/watch?v=YL260-A5r2U
    if (tree->root == NULL) {
        puts("Tree is empty, breaking...");
        return 0;
    }
    printf("name of file: tree.gv\nname of picture: tree.png\n");

    FILE* Fin = fopen("tree.gv", "w");
    fwrite("digraph G {\n", sizeof(char), 11, Fin);

    graph(Fin, tree->root);

    fwrite("\n}", sizeof(char),2,Fin);
    fclose(Fin);

    int n = system("dot -v -Tpng tree.gv -o tree.png"); //пишет в консоли
    printf("Result: = %d\n", n);
    if (n != 0)
        puts("Error!");
    return 1;
}

int D_Time(Tree* tree) {
    if (tree)
        free_tree(tree->root);

    const char* msgs[] = {"0.Quit", "1.Add", "2.Find on key", "3.Delete", "4.Special find",
                          "5.Traversal"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int rc;
    int (*fptr[])(Tree*) = {NULL, T_Add, T_keyFind, T_Delete, T_specFind, T_Traversal};
    while (rc = dialog(msgs, NMsgs)) {
        if (rc == 0)
            break;
        int timetest = 0;
        for (int i = amount; i <= amount * 10; i += amount) {
            srand(time(NULL));
            tree = rand_data(tree, i);
            printf("%d nodes:\n", i);
            for (int j = 0; j < 10; j++) {
                int tmp = j;

                clock_t begin = clock();
                if (!fptr[rc](tree)) {
                    j--;
                }
                clock_t end = clock();
                timetest += end - begin;
                if (j == tmp) {
                    //printf("case %d - %.5lf seconds\n", j + 1, (double) timetest / 10 / CLOCKS_PER_SEC);
                    printf("%.5lf\n",(double) timetest / 10 / CLOCKS_PER_SEC);
                }
                free_tree(tree->root);
            }
            puts("");
        }
    }
    printf("End of timing...\n");
    return 1;
}