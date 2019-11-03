#ifndef LIST_H
#define LIST_H

#include "collisionbox.h"

typedef struct dataNode
{
    CollisionBox *value;
} DataNode;

typedef struct node
{
    DataNode data;
    struct node *next;
} Node;

typedef struct list
{
    int size;
    Node *head;
} List;

List *createList();
void push(List *list, DataNode data);
void pop(List *list);
int empty_list(List *list);
Node *atpos(List *list, int index);
int indexof(List *list, DataNode node);
void remove_at(List *list, int index);
void insert(List *list, DataNode data, int index);
void destroy_list(List *list);

#endif // !LIST_H