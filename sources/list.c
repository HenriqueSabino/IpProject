#include <stdio.h>
#include <stdlib.h>
#include "../headers/list.h"

List *createList()
{
    List *list = (List *)malloc(sizeof(List));

    list->size = 0;
    list->head = NULL;

    return list;
}

void push(List *list, DataNode data)
{
    //lastNode->newNode
    //push(0->1->2->3, 4) => 0->1->2->3->4

    //new node to add
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    //checking if the list is empty
    if (!empty_list(list))
    {
        //looking for the last node
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = node;
        list->size++;
    }
    else
    {
        list->head = node;
        list->size++;
    }
}

int empty_list(List *list)
{
    return (list->size == 0);
}

void pop(List *list)
{
    if (!empty_list(list))
    {
        Node *previous = NULL;
        Node *current = list->head;

        //seeking for the last node parent
        while (current->next != NULL)
        {
            previous = current;
            current = current->next;
        }

        previous->next = NULL;
        free(current);
    }
}

Node *atpos(List *list, int index)
{
    if (index >= 0 && index < list->size)
    {
        Node *node = list->head;

        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        return node;
    }

    return NULL;
}

int indexof(List *list, DataNode node)
{
    Node *pointer = list->head;

    int index = 0;

    while (pointer != NULL && pointer->data.value != node.value)
    {
        pointer = pointer->next;
        index++;
    }

    return (index >= list->size) ? -1 : index;
}

void remove_at(List *list, int index)
{
    if (index == 0)
    {
        Node *old_head = list->head;
        Node *new_head = old_head->next;

        list->head = new_head;
        free(old_head);
        list->size--;
    }
    else
    {
        Node *current = atpos(list, index);

        if (current != NULL)
        {
            Node *previous = atpos(list, index - 1);
            previous->next = current->next;

            free(current);
            list->size--;
        }
    }
}

void insert(List *list, DataNode data, int index)
{
    if (index == 0)
    {
        Node *old_head = list->head;

        Node *new_head = (Node *)malloc(sizeof(Node));
        new_head->data = data;

        new_head->next = old_head;
        list->head = new_head;

        list->size++;
    }
    else
    {
        Node *current = atpos(list, index);

        if (current != NULL)
        {
            Node *previous = atpos(list, index - 1);

            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->data = data;

            previous->next = new_node;
            new_node->next = current;
            list->size++;
        }
    }
}

void destroy_list(List *list)
{
    for (int i = list->size - 1; i >= 0; i--)
    {
        remove_at(list, i);
    }

    free(list);
    list = NULL;
}