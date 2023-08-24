#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *newList = (List *)calloc(1, sizeof(List));
    if (newList == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la lista.\n");
        exit(EXIT_FAILURE);
    }
    return newList;    
}

void * firstList(List * list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }    
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) {
        fprintf(stderr, "Error: El current no está configurado o la lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->current->next;
    if (list->current == NULL) {
        fprintf(stderr, "Error: No hay un nodo siguiente.\n");
        return NULL;
    }    
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) {
        fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) {
        fprintf(stderr, "Error: El current no está configurado o la lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->current->prev;
    if (list->current == NULL) {
        fprintf(stderr, "Error: No hay un nodo anterior.\n");
        return NULL;
    }
    
    return list->current->data;
}

void pushFront(List * list, void * data) {
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}