#ifndef VQ_ARRAY_LIST_H
#define VQ_ARRAY_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#ifndef VQ_DEF_TYPE
#define VQ_DEF_TYPE extern
#endif // VQ_DEF_TYPE

#define VQ_ARRAY_LIST_IMPLEMENTATION

#ifndef VQ_DEFAULT_ARRAY_LIST_SIZE
#define VQ_DEFAULT_ARRAY_LIST_SIZE 8
#endif

  typedef struct array_list array_list_t;

  VQ_DEF_TYPE array_list_t* array_list_new(size_t element_size);
  VQ_DEF_TYPE void array_list_destroy(array_list_t* list);

  VQ_DEF_TYPE size_t array_list_get_size(array_list_t* list);

  VQ_DEF_TYPE void array_list_add(array_list_t* list, void* element);
  VQ_DEF_TYPE void array_list_contains(array_list_t* list, void* element);
  VQ_DEF_TYPE void array_list_remove(array_list_t* list, void* element);
  VQ_DEF_TYPE void* array_list_get_at(array_list_t* list, unsigned int index);
  VQ_DEF_TYPE void array_list_remove_at(array_list_t* list, unsigned int index);
  VQ_DEF_TYPE void array_list_clear(array_list_t* list);

#ifdef __cplusplus
}
#endif

#ifdef VQ_ARRAY_LIST_IMPLEMENTATION


#include <stdlib.h>

typedef struct array_list {
  size_t element_size;
  size_t count;
  size_t capacity;
  void** data;
} array_list_t;

static void resize(array_list_t* list) {
  list->capacity = list->capacity << 1;
  list->data = (void**)realloc(list->data, list->element_size * list->capacity);
}

array_list_t* array_list_new(size_t element_size) {
  array_list_t* new_array_list = (array_list_t*)malloc(sizeof(array_list_t));
  new_array_list->element_size = element_size;
  new_array_list->count = 0;
  new_array_list->capacity = VQ_DEFAULT_ARRAY_LIST_SIZE;
  new_array_list->data = (void**)malloc(sizeof(void*) * VQ_DEFAULT_ARRAY_LIST_SIZE);
  return new_array_list;
}

void array_list_destroy(array_list_t* list) {
  free(list->data);
  free(list);
}

size_t array_list_get_size(array_list_t* list) {
  return list->count;
}

void array_list_add(array_list_t* list, void* element) {
  if (list->count == list->capacity)
    resize(list);

  size_t index = list->count;
  list->data[index] = element;
  list->count++;
}

void array_list_contains(array_list_t* list, void* element) {}

void array_list_remove(array_list_t* list, void* element) {}

void* array_list_get_at(array_list_t* list, unsigned int index) {
  return list->data[index];
}

void array_list_remove_at(array_list_t* list, unsigned int index) {}

void array_list_clear(array_list_t* list) {}

#endif

#endif