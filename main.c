#include <stdio.h>
#include "list.h"

struct Data_impl { int x; };
typedef struct Data_impl Data;

void printData(void* data) {
    printf("%d ", *((int*)data));
}

void* createData(int x) {
    Data* data = malloc(sizeof(Data));
    data->x = x;
    return data;
}
void* copyData(void* data) {
    return createData(((Data*)data)->x);
}

int removeCond(void* data) {
    return ((Data*)data)->x % 2 == 0;
}

int compareLess(void* a, void* b) {
    // int x = ((Data*)a)->x, y = ((Data*)b)->x;
    return ((Data*)a)->x <= ((Data*)b)->x;
}

int main() {
    List* list = createList(free);
    for(int i = 20; i >= 0; --i) {
        pushTailData(list, createData(i));
    }
    printf("Pure  : ");
    map(list, printData);
    
    printf("\nModify: ");
    insertData(list, list->head->next, createData(666));
    insertData(list, list->tail->prev, createData(777));
    insertData(list, list->tail, createData(888));
    insertData(list, list->head, createData(555));
    map(list, printData);
    
    
    printf("\nRemove: ");
    removeAll(list, removeCond);
    map(list, printData);
    
    printf("\nCopied: ");
    List* copied = copyList(list, copyData);
    map(copied, printData);
    
    int n = 0;
    printf("\nSort B: ");
    n = sortBubble(list, compareLess);
    mapr(list, printData);
    printf("| watches: %d", n);
    
    printf("\nSort S: ");
    n = sortSelection(copied, compareLess);
    mapr(copied, printData);
    printf("| watches: %d", n);
    
}
