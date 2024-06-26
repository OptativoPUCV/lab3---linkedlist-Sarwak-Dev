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

  List * new = (List *)malloc(sizeof(List));
  
  new->head = NULL;
  new->tail = NULL;
  new->current = NULL;
    
     return new;
}

void * firstList(List * list) {
  
    list->current = list->head;
    if (list->current)
      return list->current->data;
    return NULL;
}

void * nextList(List * list) {

  if (list->current != NULL) {
    if (list->current->next != NULL) {
      list->current = list->current->next;
      return list->current->data;
    }
  }
  return NULL;
}

void * lastList(List * list) {

  list->current = list->tail;
  if (list->current)
    return list->current->data;
  return NULL;

}

void * prevList(List * list) {

  if (list->current != NULL) {
    if (list->current->prev != NULL) {
      list->current = list->current->prev;
      return list->current->data;
    }
  }
  
    return NULL;
}

void pushFront(List *list, void *data) {
    Node *newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->next = list->head; 
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) {
    Node *newNode = createNode(data);
  
        newNode->next = list->current->next;
        newNode->prev = list->current;
        list->current->next = newNode;
        if (list->current == list->tail) {
            list->tail = newNode;
        }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List *list) {
    Node *nodeToRemove = list->current;

    if (list->current->prev != NULL) {
        list->current->prev->next = list->current->next;
    } 
    else {
        list->head = list->current->next;
    }

    if (list->current->next != NULL) {
        list->current->next->prev = list->current->prev;
    } 
    else {
        list->tail = list->current->prev;
    }

    list->current = list->current->next;
    void *data = nodeToRemove->data;

    free(nodeToRemove);

    return data; 
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}