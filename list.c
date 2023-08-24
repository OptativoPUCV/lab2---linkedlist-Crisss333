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
        //fprintf(stderr, "Error: No se pudo asignar memoria para la lista.\n");
        exit(EXIT_FAILURE);
    }
    return newList;    
}

void * firstList(List * list) {
    if (list->head == NULL) {
        //fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }    
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) {
        //fprintf(stderr, "Error: El current no está configurado o la lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->current->next;
    if (list->current == NULL) {
        //fprintf(stderr, "Error: No hay un nodo siguiente.\n");
        return NULL;
    }    
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) {
        //fprintf(stderr, "Error: La lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) {
        //fprintf(stderr, "Error: El current no está configurado o la lista está vacía.\n");
        return NULL;
    }
    
    list->current = list->current->prev;
    if (list->current == NULL) {
        //fprintf(stderr, "Error: No hay un nodo anterior.\n");
        return NULL;
    }
    
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL) {
        //fprintf(stderr, "Error: El current no está configurado.\n");
        return NULL;
    }
    
    Node *newNode = createNode(data);
    
    newNode->next = list->current->next;
    if (list->current->next != NULL) {
        list->current->next->prev = newNode;
    } else {
        // Si el nodo actual es el último nodo, actualiza la cola de la lista
        list->tail = newNode;
    }
    
    newNode->prev = list->current;
    list->current->next = newNode;
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
    if (list->current == NULL) {
        //fprintf(stderr, "Error: El current no está configurado.\n");
        return NULL;
    }

    Node *nodeToRemove = list->current;
    void *data = nodeToRemove->data;

    if (nodeToRemove == list->head) {
        list->head = nodeToRemove->next;
    } else {
        nodeToRemove->prev->next = nodeToRemove->next;
    }

    if (nodeToRemove == list->tail) {
        list->tail = nodeToRemove->prev;
    } else {
        nodeToRemove->next->prev = nodeToRemove->prev;
    }

    if (nodeToRemove->next != NULL) {
        list->current = nodeToRemove->next;
    } else {
        list->current = nodeToRemove->prev;
    }

    free(nodeToRemove);

    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}