#ifndef TESTC_CLION_LIST_H
#define TESTC_CLION_LIST_H

#include <stdlib.h>

struct Node_impl;
typedef struct Node_impl Node;
struct Node_impl {
    void* data;
    Node *prev, *next;
};

struct List_impl {
    int size;
    Node *head, *tail;
    void (*data_deleter)(void* data);
};
typedef struct List_impl List;

List* map(List* list, void(*f)(void* data));
List* mapr(List* list, void(*f)(void* data));

List* createList(void (*deleter)(void* data));
List* copyList(List* list);

void pushFront(List* list, void* data);
void pushTailData(List* list, void* data);
void insertData(List* list, Node* at_before, void* data);

void popFront(List* list);
void popTail(List* list);
Node* erase(List* list, Node* node);
void removeAll(List* list, int (*is_remove)(void* data));

int sortBubble(List* list, int (*is_order_correct)(void* a, void* b));
int sortSelection(List* list, int (*is_order_correct)(void* a, void* b));

#endif //TESTC_CLION_LIST_H
