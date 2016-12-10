/*! \file array.h
 * \brief provides macros for the resizable array data structure. Allowing for generic versions.
 *
 * **This is a header only file for a generic data structure.**
 *
 * **Usage:**
 *
 * Required definitions for an int array
 *
 *      ARRAY_DEC(int) 
 *      ARRAY_DEF(int)
 *      
 * Create an array of ints that has an initial capacity of 1000.
 *
 *      ARRAY(int) array_of_ints = ARRAY_CREATE(int,1000);
 *
 * Add an int to the front of the array.
 *
 *      ARRAY_ADD(int,&array_of_ints,5);
 *
 * Insert an int to the 101th index of the array.
 * 
 *      ARRAY_INSERT(int,&array_of_ints,7,100);
 *
 * Get a reference to the added int from the array.
 *
 *      ARRAY_GET(int,&array_of_ints,0) == 5; //this is true
 *
 * Clean up the array.
 *
 *      ARRAY_DESTROY(int,&array_of_ints);
 */
#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>

#define ARRAY(type) array_of_##type

#define ARRAY_CREATE(type,init_cap) array_of_##type##_create(init_cap)

#define ARRAY_DESTROY(type,array) array_of_##type##_destroy(array)

#define ARRAY_ADD(type,array,data) array_of_##type##_add(array,data)

#define ARRAY_EXPAND(type,array,amount) array_of_##type##_expand(array,amount)

#define ARRAY_INSERT(type,array,data,index) array_of_##type##_insert(array,data,index)

#define ARRAY_GET(type,array,index) array_of_##type##_get(array,index)

#define ARRAY_DEC(type)\
typedef struct ARRAY(type){\
    type* array;\
    size_t size;\
    size_t capacity;\
}ARRAY(type);\
ARRAY(type) array_of_##type##_create(size_t init_cap);\
void array_of_##type##_destroy(array_of_##type* array);\
size_t array_of_##type##_add(array_of_##type* array,type data);\
void array_of_##type##_expand(array_of_##type* arrjy,size_t amount);\
void array_of_##type##_insert(array_of_##type* array,type data,size_t index);\
type* array_of_##type##_get(array_of_##type* array,size_t index);\

#define ARRAY_DEF(type)\
ARRAY(type) array_of_##type##_create(size_t init_cap){\
    ARRAY(type) output = {malloc(sizeof(type) * init_cap),0,init_cap};\
    return output;\
}\
void array_of_##type##_destroy(array_of_##type* array){\
    free(array->array);\
    array->array = NULL;\
    array->size = 0;\
    array->capacity = 0;\
}\
size_t array_of_##type##_add(array_of_##type* array,type data){\
    if(array->size >= array->capacity)\
        ARRAY_EXPAND(type,array,array->capacity*2);\
    array->array[array->size++] = data;\
    return array->size -1;\
}\
void array_of_##type##_expand(array_of_##type* array,size_t amount){\
    type* tmp_array = realloc(array->array,sizeof(type)* amount);\
    array->array  = tmp_array;\
}\
void array_of_##type##_insert(array_of_##type* array,type data,size_t index){\
    if(index >= array->capacity)\
        ARRAY_EXPAND(type,array,index);\
    array->array[index] = data;\
    array->size = ++index;\
}\
type* array_of_##type##_get(array_of_##type* array,size_t index){\
    if(index < array->size){\
        return &array->array[index];\
    }\
    return NULL;\
}\

#endif



