// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <assert.h>
#include <stdio.h>
#include "list.h"

List* map(List* list, void(*f)(void* data)) {
    Node* cur = list->head;
    while(cur != NULL) f(cur->data), cur = cur->next;
    return list;
}
List* mapr(List* list, void(*f)(void* data)) {
    Node* cur = list->tail;
    while(cur != NULL) f(cur->data), cur = cur->prev;
    return list;
}

List* createList(void (*deleter)(void* data)) {
    List* list = (List*) malloc(sizeof(List));
    list->head = list->tail = NULL;
    list->data_deleter = deleter;
    list->size = 0;
    return list;
}
List* copyList(List* list) {
    List* copied = createList(list->data_deleter);
    Node* cur = list->head;
    while(cur != NULL) {
        pushTailData(copied, cur->data);
        cur = cur->next;
    }
    return copied;
}

Node* createNode(void* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->next = node->prev = NULL;
    node->data = data;
    return node;
}

void pushFrontNode(List* list, Node* new_node) {
    if(list->size < 1) {
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    
    list->size += 1;
}
void pushTailNode(List* list, Node* new_node) {
    if(list->size < 1) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    
    list->size += 1;
}
void insertNodeBefore(List* list, Node* at_before, Node* new_node) {
    if(at_before == list->head) {
        pushFrontNode(list, new_node);
        return;
    }
    if(at_before->prev != NULL) at_before->prev->next = new_node;
    new_node->prev = at_before->prev;
    new_node->next = at_before;
    at_before->prev = new_node;
    list->size += 1;
}

void pushFrontData(List* list, void* data) {
    pushFrontNode(list, createNode(data));
}
void pushTailData(List* list, void* data) {
    pushTailNode(list, createNode(data));
}
void insertData(List* list, Node* at_before, void* data) {
    insertNodeBefore(list, at_before, createNode(data));
}

Node* extractHead(List* list) {
    Node* extracted = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->size -= 1;
    extracted->prev = extracted->next = NULL;
    return extracted;
}
Node* extractTail(List* list) {
    Node* extracted = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    list->size -= 1;
    extracted->prev = extracted->next = NULL;
    return extracted;
}
Node* extractNode(List* list, Node* extracted) {
    if(extracted == list->head) return extractHead(list);
    if(extracted == list->tail) return extractTail(list);
    
    Node *prev = extracted->prev, *next = extracted->next;
    extracted->prev = extracted->next = NULL;
    prev->next = next;
    next->prev = prev;
    list->size -= 1;
    return extracted;
}

void freeNode(List* list, Node* node) {
    list->data_deleter(node->data);
    free(node);
}
void popFront(List* list) {
    freeNode(list, extractHead(list));
}
void popTail(List* list) {
    freeNode(list, extractTail(list));
}
Node* erase(List* list, Node* node) {
    Node* next = node->next;
    freeNode(list, extractNode(list, node));
    return next;
}
void removeAll(List* list, int (*is_remove)(void* data)) {
    Node* cur = list->head;
    while(cur != NULL) cur = is_remove(cur->data) ? erase(list, cur) : cur->next;
}

void swapNodes(Node* a, Node* b) {
    if(a == b) return;
    void* a_data = a->data;
    a->data = b->data;
    b->data = a_data;
}
int sortBubble(List* list, int (*is_order_correct)(void* a, void* b)) {
    int n = 0;
    for(int i = 0; i < list->size - 1; ++i) {
        for(Node* cur = list->head; cur->next != NULL; cur = cur->next) {
            if(!is_order_correct(cur->data, cur->next->data)) {
                swapNodes(cur, cur->next);
            }
            n = n + 1;
        }
    }
    return n;
}
int sortSelection(List* list, int (*is_order_correct)(void* a, void* b)) {
    int n = 0;
    for(Node* a = list->head; a->next != NULL; a = a->next) {
        Node* min = a;
        for(Node* b = a->next; b != NULL; b = b->next) {
            if(!is_order_correct(min->data, b->data)) {
                min = b;
            }
            n = n + 1;
        }
        swapNodes(a, min);
    }
    return n;
}