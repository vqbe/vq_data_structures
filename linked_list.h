#ifndef VQBE_LINKED_LIST_H
#define VQBE_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#ifndef VQBE_DEF_TYPE
#define VQBE_DEF_TYPE extern
#endif // VQBE_DEF_TYPE

  typedef struct linked_list_iterator linked_list_iterator_t;
  typedef struct linked_list_node linked_list_node_t;
  typedef struct linked_list linked_list_t;

  VQBE_DEF_TYPE linked_list_iterator_t* linked_list_create_iterator(linked_list_t* list);
  VQBE_DEF_TYPE bool linked_list_it_has_next(linked_list_iterator_t* it);
  VQBE_DEF_TYPE void* linked_list_it_get_next(linked_list_iterator_t* it);

  VQBE_DEF_TYPE linked_list_t* linked_list_new();
  VQBE_DEF_TYPE void linked_list_destroy(linked_list_t* list);

  VQBE_DEF_TYPE size_t linked_list_get_size(linked_list_t* list);

  VQBE_DEF_TYPE void linked_list_push(linked_list_t* list, void* element);
  VQBE_DEF_TYPE void linked_list_push_back(linked_list_t* list, void* element);
  VQBE_DEF_TYPE void linked_list_contains(linked_list_t* list, void* element);
  VQBE_DEF_TYPE void linked_list_remove(linked_list_t* list, void* element);
  VQBE_DEF_TYPE void* linked_list_get(linked_list_t* list, unsigned int index);
  VQBE_DEF_TYPE void linked_list_remove_at(linked_list_t* list, unsigned int index);
  VQBE_DEF_TYPE void linked_list_clear(linked_list_t* list);

#ifdef __cplusplus
}
#endif

#ifdef VQBE_LINKED_LIST_IMPLEMENTATION

#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list_node {
  void* data;
  struct linked_list_node* next;
} linked_list_node_t;

typedef struct linked_list {
  linked_list_node_t* head;
  size_t count;
} linked_list_t;

typedef struct linked_list_iterator {
  linked_list_t* list;
  linked_list_node_t* current_node;
} linked_list_iterator_t;

linked_list_iterator_t* linked_list_create_iterator(linked_list_t* list) {
  linked_list_iterator_t* it = (linked_list_iterator_t*)malloc(sizeof(linked_list_iterator_t));
  it->list = list;
  it->current_node = list->head;

  return it;
}

bool linked_list_it_has_next(linked_list_iterator_t* it) {
  return it->current_node != NULL;
}

void* linked_list_it_get_next(linked_list_iterator_t* it) {
  if (it->current_node != NULL) {
    void* data = it->current_node->data;
    it->current_node = it->current_node->next;

    return data;
  }

  return (void*)NULL;
}

linked_list_t* linked_list_new() {
  linked_list_t* new_linked_list = (linked_list_t*)malloc(sizeof(linked_list_t));
  new_linked_list->count = 0;
  new_linked_list->head = NULL;
  return new_linked_list;
}

void linked_list_destroy(linked_list_t* list) {
  linked_list_node_t* node = list->head;
  while (node != NULL) {
    node = node->next;
    free(node);
  }
  free(list);
}

size_t linked_list_get_size(linked_list_t* list) {
  return list->count;
}

void linked_list_push(linked_list_t* list, void* element) {
  // Create node
  linked_list_node_t* node = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));
  node->data = element;
  node->next = list->head;

  // Set new head
  list->head = node;
  list->count++;
}

void linked_list_push_back(linked_list_t* list, void* element) {
  // Create node
  linked_list_node_t* node = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));
  node->data = element;
  node->next = NULL;

  linked_list_node_t* tmp = list->head;

  if (tmp == NULL) {
    // First element
    list->head = node;
    return;
  }

  // Iterate until end
  while (tmp->next != NULL)
    tmp = tmp->next;

  tmp->next = node;
  list->count++;
}

void linked_list_contains(linked_list_t* list, void* element) {}

void linked_list_remove(linked_list_t* list, void* element) {}

void* linked_list_get(linked_list_t* list, unsigned int index) {
  return (void*)NULL;
}

void linked_list_remove_at(linked_list_t* list, unsigned int index) {}

void linked_list_clear(linked_list_t* list) {}

#endif

#endif