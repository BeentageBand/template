#include "cvector-internal.h"
#include <string.h>

static void cvector_t_delete(union CVector_T * const cvector_t);
static size_t cvector_t_size(union CVector_T * const);
static void cvector_t_clear(union CVector_T * const);
static void cvector_t_reserve(union CVector_T * const, size_t const);
static T * cvector_t_begin(union CVector_T * const);
static T * cvector_t_end(union CVector_T * const);
static T * cvector_t_at(union CVector_T * const, size_t const);
static T cvector_t_access(union CVector_T * const, size_t const);
static void cvector_t_push_back(union CVector_T * const, T const);
static T cvector_t_back(union CVector_T * const);
static void cvector_t_pop_back(union CVector_T * const);


void cvector_t_override(union CVector_T_Class * const clazz)
{
  clazz->Class.destroy = (Class_Delete_T) cvector_t_delete;
  clazz->size = cvector_t_size;
  clazz->clear = cvector_t_clear;
  clazz->reserve = cvector_t_reserve;
  clazz->begin = cvector_t_begin;
  clazz->end = cvector_t_end;
  clazz->at = cvector_t_at;
  clazz->access = cvector_t_access;
  clazz->back = cvector_t_back;
  clazz->push_back = cvector_t_push_back;
  clazz->pop_back = cvector_t_pop_back;
}

void cvector_t_delete(union CVector_T * const cvector_t)
{
  CVector_T_clear(cvector_t);
  cvector_t->buffer = NULL;
  cvector_t->capacity = 0;
}
 
void CVector_T_populate(union CVector_T * const cvector_t)
{
    Object_populate(&cvector_t->Object, &Get_CVector_T_Class()->Class);
    cvector_t->buffer = NULL;
    cvector_t->capacity = 0;
    cvector_t->i = 0;
    CVector_T_reserve(cvector_t, 5);
}

T * cvector_t_begin(union CVector_T * const cvector_t)
{
    return cvector_t->buffer;
}

T * cvector_t_end(union CVector_T * const cvector_t)
{
    return cvector_t->buffer + cvector_t->vtbl->size(cvector_t);
}

T cvector_t_back(union CVector_T * const cvector_t)
{
    return cvector_t->buffer[cvector_t->i - 1];
}

void cvector_t_push_back(union CVector_T * const cvector_t, T const value)
{
  if (cvector_t->i >= cvector_t->capacity)
  {
    CVector_T_reserve(cvector_t, cvector_t->i * 2);
  }

  memcpy(cvector_t->buffer +cvector_t->i, &value, sizeof(value));
  ++cvector_t->i;
}

void cvector_t_pop_back(union CVector_T * const cvector_t)
{
   if(cvector_t->i)
   {
      --cvector_t->i;
#ifdef CVECTOR_DELETABLE
      Object_Delete((struct Object *(cvector_t->buffer+cvector_t->i));
#else
      memset(cvector_t->buffer + cvector_t->i, 0, sizeof(cvector_t->buffer[cvector_t->i]));
#endif
   }
}

size_t cvector_t_size(union CVector_T * const cvector_t)
{
    return cvector_t->i;
}

T * cvector_t_at(union CVector_T * const cvector_t, size_t index)
{
    return cvector_t->buffer+index;
}

T cvector_t_access(union CVector_T * const cvector_t, size_t index)
{
    return cvector_t->buffer[index];
}

size_t cvector_t_capacity(union CVector_T * const cvector_t)
{
    return cvector_t->capacity;
}

void cvector_t_clear(union CVector_T * const cvector_t)
{
    while(cvector_t->i)
   {
      CVector_T_pop_back(cvector_t);
   }
}

void cvector_t_reserve(union CVector_T * const cvector_t, size_t const n)
{
  if (n <= cvector_t->capacity) return;

  T * old_buff = cvector_t->buffer;
  size_t old_capacity = cvector_t->capacity;
  cvector_t->capacity = n;
  cvector_t->buffer = (T *) malloc(cvector_t->capacity * sizeof(T));
  memcpy(cvector_t->buffer, old_buff, sizeof(T) * old_capacity);

  if(old_buff) free(old_buff);
}
