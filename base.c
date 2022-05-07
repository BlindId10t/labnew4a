#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "base.h"

int getInt (int* a) {
    int n;
    do {
        n = scanf("%d", a);
        scanf("%*[^\n]");
        if (n < 0)
            return 0;
        if (n == 0 || a < 0) {
            printf("Error! Not an unsigned int number! Repeat...\n");
            scanf("%*c");
        }
    } while (n==0);
    return 1;
}

void free_stack(Stack* stack) {
    for (int i = 0; i < stack->size; i++) {
        stack->data[i] = NULL;
    }
    stack->size = 0;
}

void printStackValue(Node* value) {
    printf("%d", value->info);
}

void show_stack(Stack stack, void (*printStackValue)(Node*)) {
    int i;
    int len = stack.size - 1;
    printf("stack with size %d > ", stack.size);
    for (i = 0; i < len; i++) {
        printStackValue(stack.data[i]);
        printf(" | ");
    }
    if (stack.size != 0) {
        printStackValue(stack.data[i]);
    }
    printf("\n");
}

void push (Stack* stack, Node* value) {
    if (stack->size >= STACK_MAX_SIZE)
        return;
    stack->data[stack->size] = value;
    stack->size++;
}


#ifndef sew
Node* insert(Tree* tree, int key, int info, int* flag) {
    Node* new_node = (Node*)calloc(1,sizeof(Node));
    new_node->info = info;
    new_node->key = key;
    if (tree->root == NULL) {
        tree->root = new_node;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    Node* ptr = tree->root;
    Node* par = NULL;
    while (ptr != NULL) {
        par = ptr;
        if (new_node->key < ptr->key)
            ptr = ptr->left;
        else if (new_node->key > ptr->key)
            ptr = ptr->right;
        else {
            *flag = 1;
            return ptr;
        }
    }
    if (new_node->key < par->key)
        par->left = new_node;
    else par->right = new_node;
    return new_node;
}

Node* FindByKey(Node* root, int key) {
    Node* ptr = root;
    if (ptr == NULL)
        return NULL;
    if (key == ptr->key)
        return ptr;
    if (key < ptr->key)
        return FindByKey(ptr->left, key);
    return FindByKey(ptr->right, key);
}

Node* find_min(Node* root) {
    if (root == NULL) {
        return NULL;
    } else if (root->left == NULL) {
        return root;
    } else {
        return find_min(root->left);
    }
}

Node* delete_node(Node* root, int key) {

    Node* x;
    Node* tmp_cell;

    if (root == NULL) return NULL;

    if (key < root->key) {
        root->left = delete_node(root->left, key );
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else if (root->left && root->right) {
        tmp_cell = find_min(root->right);
        root->key = tmp_cell->key;
        root->right = delete_node(root->right, root->key);
    } else {
        tmp_cell = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        free(tmp_cell);
    }

    return root;
}

Stack find_spec (Node* root, int key, Stack* stack) {
    Node* pClosest = NULL;
    int minDistance = 10000000;
    Node* pNode = root;
    while(pNode != NULL) {
        int distance = minDistance;
        if(distance < minDistance){
            minDistance = distance;
            pClosest = pNode;
        }
        if(distance == 0) {
            puts("there is already node with that key!");
            break;
        }
        if(pNode->key > key)
            pNode = pNode->left;
        else if(pNode->key < key)
            pNode = pNode->right;
    }
    if (pClosest != 0) {
        push(stack, pClosest);
        int dist = abs(pClosest->key - key);
        int key1 = key + dist;
        int key2 = key - dist;
        Node* node1 = FindByKey(root, key1);
        Node* node2 = FindByKey(root, key2);
        if (node1 != 0) {
            push(stack, node1);
        }
        else push(stack, node2);
    }
    return *stack;
}

void traversal(Node* root, int left_b, int right_b, int flag) {
    while (root) {
        //если левого поддерева нет, то выведи текущее значение и иди направо
        if (root->left == NULL) {
            if ((root->key < left_b || root->key > right_b) && flag == 0)
                printf("%d ", root->info);
            root = root->right;
        }
        else { //если есть левое поддерево
            Node* current = root->left;
            while (current->right != NULL && current->right != root) //иди по левому поддереву вправо пока не дойдешь до конца или текущего узла
                current = current->right;

            //если правый потомок совпадает с текущим корнем, то обнули потомка и смени текущий узел
            if (current->right == root) {
                current->right = NULL;
                root = root->right;
            }
            else { //иначе сделай правого потомка указывающим на текущий узел и иди влево
                if ((root->key < left_b || root->key > right_b) && flag == 0)
                    printf("%d ", root->info);
                current->right = root;
                root = root->left;
            }
        }
    }
}

Node* free_tree(Node* ptr) {
    if (ptr != NULL) {
        free_tree(ptr->left);
        free_tree(ptr->right);
        free(ptr);
    }
    return NULL;
}
#endif

#ifdef sew

Node* make_node(int key, int info) {
    Node* new_node = (Node*)calloc(1,sizeof(Node));
    new_node->info = info;
    new_node->key = key;
    new_node->link[0] = NULL;
    new_node->link[1] = NULL;
    new_node->thread = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert (Tree *tree, int key, int info, int* flag) {
    Node *it = tree->root, *q;
    if (tree->root == NULL) {
        tree->root = make_node(key, info);
        return tree->root;
    }
    else {
        int dir;
        for ( ; ; ) {
            dir = it->key < key; //как в поиске

            if (it->key == key) {
                *flag = 1;
                return it;
            }
            else if (dir == 1 && it->thread == 1)
                break;
            else if (it->link[dir] == NULL)
                break;

            it = it->link[dir];
        }

        q = make_node (key, info);
        if (dir == 1) {
            q->link[1] = it->link[1];
            it->thread = 0;
        }
        else q->link[1] = it;
        if (dir == 0) {
            it->left = q;
        }
        else it->right = q;
        it->link[dir] = q;
    }
    return it;
}

Node* FindByKey(Node* root, int key) {
    Node *it = root;
    int dir;
    for ( ; ; ) {
        dir = it->key < key; //1 если меньше, 0 если больше или равно
        if (it->key == key)
            return it;
        else if ( dir == 1 && it->thread == 1 )
            break;
        else if ( it->link[dir] == NULL )
            break;
        it = it->link[dir];
    }
    return it;
}

Node* delete_node(Node* root, int key) {
   if (root != NULL) {
       Node head = {0}; //новый корень
       Node* it = &head;
       Node *q, *p, *f = NULL;
       int dir = 1;
       it->link[1] = root;
       //находим узел для удаления (f)
       while (it->link[dir] != NULL) {
           if (dir == 1 && it->thread == 1)
               break;

           p = it;
           it = it->link[dir];
           dir = it->key <= key;

           if (it->key == key)
               f = it;
       }

       if (f != NULL) {
           q = it->link[it->link[0] == NULL]; //если нет левого узла, то q это threat
           dir = p->link[1] == it;
           f->key = it->key;
           f->info = it->info;
           if (p == q)
               p->link[0] = NULL;
           else if (it->link[0] == NULL && it->thread) {
               p->thread = 1;
               p->link[1] = it->link[1];
           }
           else if (it->link[0] == NULL) {
               p->link[dir] = q;
           }
           else {
               q->thread = it->thread;
               q->link[1] = it->link[1];
               p->link[dir] = q;
           }
           free (it);
       }
       root = head.link[1];
   }
   return root;
}

int first_trav (Node** it, Node* root) {
    *it = root;

   if (*it != NULL) {
     while ((*it)->link[0] != NULL)
         (*it) = (*it)->link[0];
   }

   if ((*it) != NULL)
       return (*it)->info;
  else
        return -1;
}

int next_trav (Node** it) {
   if ((*it)->thread == 0) {
       (*it) = (*it)->link[1];
       if ((*it) != NULL) {
            while ((*it)->link[0] != NULL)
                (*it) = (*it)->link[0];
       }
   }
   else (*it) = (*it)->link[1];
   if ((*it) != NULL)
        return (*it)->info;
   else
        return -1;
 }


void traversal(Node* root, int left_b, int right_b, int flag) {
    Node** ptr;
    int first = first_trav(ptr, root);
    if (first != -1) {
        if ((first < left_b || first > right_b) && flag == 0)
            printf("%d ", first);
        int next;
        do {
            next = next_trav(ptr);
            if (next != -1) {
                if ((first < left_b || first > right_b) && flag == 0)
                    printf("%d ", next);
            }
        } while (next != -1);
    }
}

Stack find_spec (Node* root, int key, Stack* stack) {
    return *stack;
}

Node* free_tree(Node* ptr) {
    return NULL;
}

#endif