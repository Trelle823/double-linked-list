/*
 * Removing duplicate values from double linked list
 *
 * Vontrelle Collins
 * 03/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct DLLNode
{
    int data;
    struct DLLNode* previous;
    struct DLLNode* next;
} DLLNode;

typedef DLLNode* DLL;

const int DLL_LENGTH = 200;
const int MAX_RANDOM = 49;

void add_random(DLL* root);
void print_dll(DLL root);
void delete_dups(DLL* root);

int main(void)
{
    srand((unsigned) time(NULL));
    DLL head = NULL;
    add_random(&head);
    printf("DLL with 200 random values:\n\n");
    print_dll(head);
    delete_dups(&head);
    printf("\n\nDLL with duplicate values removed:\n\n");
    print_dll(head);
    return 0;
}

/* 
 * Function create_dllnode
 * ---------------------
 *  data: data for node
 *
 *  returns: newly created lnode with given data
 */
DLLNode* create_dllnode(int data)
{
    DLLNode* node = malloc(sizeof(DLLNode));
    node->data = data;
    node->previous = NULL;
    node->next = NULL;

    return node;
}

/*
 * Function: add_node
 * ------------------
 *  root: pointer to head of DLL
 *  data: data of added node
 *
 *  adds new node into a linked list
 */ 
void add_node(DLL* root, int data)
{
    DLLNode* node = create_dllnode(data);

    if (!*root) {
        *root = node;
        return;
    }

    DLLNode* temp = *root;
    while (temp->next)
        temp = temp->next;

    node->previous = temp;
    temp->next = node;
}

/*
 * Function: add_random
 * --------------------
 *  root: pointer to head of DLL
 *
 *  adds random values into a linked list
 *  how many values depends on DLL_LENGTGH
 */
void add_random(DLL* root)
{
    int i, data;
    for (i = 0; i < DLL_LENGTH; ++i) {
        data = rand() % (MAX_RANDOM + 1);
        add_node(root, data);
    }   
}

/*
 * Function: delete_dups
 * ---------------------
 *  root: pointer to head of DLL
 *
 *  deletes duplicate values from a linked list
 */
void delete_dups(DLL* root)
{
    DLLNode* cur = *root;
    DLLNode* temp = NULL;
    DLLNode* delete_node = NULL;

    while (cur) {
        temp = cur->next;
        while (temp) {
            if (temp->data == cur->data) {
                delete_node = temp;
                temp = temp->next;
                delete_node->previous->next = temp;


                if (temp)
                    temp->previous = delete_node->previous;

                free(delete_node);
                continue;
            }

            temp = temp->next;
        }

        cur = cur->next;
    }

}

/* Function: print_DLL
 * -------------------
 *  root: head of DLL
 *
 *  prints data in all the nodes of DLL
 */
void print_dll(DLL root)
{
    while (root) {
        printf("%d ", root->data);
        root = root->next;
    }

    printf("\n");
}
