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

typedef struct array_list_internal array_list_internal_t;

typedef struct array_list_t {
  array_list_internal_t *m_fields;

  void (*add)(struct array_list_t *list, void *element);
  void (*contains)(struct array_list_t *list, void *element);
  void (*remove)(struct array_list_t *list, void *element);
  void (*get_at)(struct array_list_t *list, unsigned int index);
  void (*remove_at)(struct array_list_t *list, unsigned int index);
  void (*clear)(struct array_list_t *list);
} array_list_t;

VQ_DEF_TYPE array_list_t *new_array_list(size_t element_size);
VQ_DEF_TYPE void destroy_array_list(array_list_t *list);

#ifdef __cplusplus
}
#endif

#ifdef VQ_ARRAY_LIST_IMPLEMENTATION

typedef struct array_list_internal {
  size_t element_size;
  size_t count;
  size_t size;
  void **data;
} array_list_internal_t;

static void add(array_list_t *list, void *element) {}
static void contains(array_list_t *list, void *element) {}
static void remove(array_list_t *list, void *element) {}
static void get_at(array_list_t *list, unsigned int index) {}
static void remove_at(array_list_t *list, unsigned int index) {}
static void clear(array_list_t *list) {}

array_list_t *new_array_list(size_t element_size) {
  array_list_internal_t *m_fields =
      (array_list_internal_t *)malloc(sizeof(array_list_internal_t));
  m_fields->element_size = element_size;
  m_fields->count = 0;
  m_fields->size = VQ_DEFAULT_ARRAY_LIST_SIZE;
  m_fields->data = (void **)malloc(sizeof(void *) * VQ_DEFAULT_ARRAY_LIST_SIZE);

  if (m_fields->data == nullptr)
    return nullptr;

  array_list_t *new_array_list = (array_list_t *)malloc(sizeof(array_list_t));
  new_array_list->m_fields = m_fields;

  new_array_list->add = add;
  new_array_list->contains = contains;
  new_array_list->remove = remove;
  new_array_list->get_at = get_at;
  new_array_list->remove_at = remove_at;
  new_array_list->clear = clear;

  return new_array_list;
}

void destroy_array_list(array_list_t *list) {
  for (unsigned int i = 0; i < list->m_fields->size; i++) {
    free(list->m_fields->data[i]);
  }
  free(list->m_fields->data);
  free(list->m_fields);
  free(list);
}

#endif

#endif