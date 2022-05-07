#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "dialog.h"
#include "time.h"
#include "add.h"
#include "base.h"

int main() {
    Tree tree = {NULL};
    const char* msgs[] = {"0.Quit", "1.Add (WORKS)", "2.Find on key (WORKS)", "3.Delete (WORKS)",
                          "4.Special find (DOES NOT WORK... WHY???)","5.Traversal (WORKS)", "6.Show as a tree (ONE SIDE AND WITH ARROWS or REVERSED)",
                          "7.Download tree from file (WHY FILE DOES NOT OPEN?)","8.Frequency of occurrence", "9.Graphviz (WORKS)",
                          "10.Timing (WORKS)"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int rc;
    int (*fptr[])(Tree*) = {NULL, D_Add, D_keyFind, D_Delete, D_specFind, D_Traversal,
                          D_treeShow, D_Download, D_Freq, D_Graphviz, D_Time};
    while (rc = dialog(msgs, NMsgs))
        if(!fptr[rc](&tree))
            break;
    printf("That is all! End...\n");
    free_tree(tree.root);
    return 0;
}
