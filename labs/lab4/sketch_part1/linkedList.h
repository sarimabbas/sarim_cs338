#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int val;
    struct node* next;
} node;

node* lCreate();

void lDestroy(node* head);

void lAddToFront(node* head, node* addMe);

node* lFind(node* head, int val);

void lPrint(node* head);

void lPopFromFront(node* head);

bool lRemove(node* head, node* removeMe);
