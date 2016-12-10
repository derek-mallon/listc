#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#include "array.h"

#define POOL(type) pool_of_##type

#define POOL_CREATE(type,capacity) pool_of_##type##_create(capacity)
#define POOL_ADD(type,pool,item) pool_of_##type##_add(pool,item)
#define POOL_DESTROY(type,pool) pool_of_##type##_destroy(pool)
#define POOL_GET(type,pool,index) pool_of_##type##_get(pool,index)
#define POOL_FREE(type,pool,index) pool_of_##type##_free(pool,index)
#define POOL_NEXT_FREE(type,pool,index) pool_of_##type##_next_free(pool,index)
#define POOL_NEXT(type,pool) pool_of_##type##_next(pool)

#define POOL_DEC(type) \
typedef struct wrapper_of_##type{\
    type item;\
    size_t next_free;\
    uint8_t alive;\
}wrapper_of_##type;\
ARRAY_DEC(wrapper_of_##type)\
typedef struct pool_of_##type{\
    ARRAY(wrapper_of_##type) array;\
    size_t next_free;\
    size_t free;\
    size_t counter;\
}pool_of_##type;\
pool_of_##type pool_of_##type##_create(size_t capacity);\
void pool_of_##type##_add(pool_of_##type* pool,type item);\
void pool_of_##type##_destroy(pool_of_##type* pool);\
type* pool_of_##type##_get(pool_of_##type* pool,size_t index);\
void pool_of_##type##_free(pool_of_##type* pool,size_t index);\
type* pool_of_##type##_next_free(pool_of_##type* pool,size_t* index);\
type* pool_of_##type##_next(pool_of_##type* pool);\

#define POOL_DEF(type)\
ARRAY_DEF(wrapper_of_##int);\
pool_of_##type pool_of_##type##_create(size_t capacity){\
    int i;\
    pool_of_##type result;\
    result.array = ARRAY_CREATE(wrapper_of_##type,capacity);\
    result.next_free = 0;\
    result.free = 0;\
    result.counter = 0;\
    return result;\
}\
void pool_of_##type##_add(pool_of_##type* pool,type item){\
    int i;\
    wrapper_of_##type wrapper;\
    wrapper.item = item;\
    wrapper.alive = 1;\
    wrapper.next_free = pool->array.size+1;\
    if(pool->next_free == pool->array.size)\
        pool->next_free = pool->array.size+1;\
    ARRAY_ADD(wrapper_of_##type,&pool->array,wrapper);\
}\
void pool_of_##type##_destroy(pool_of_##type* pool){\
    ARRAY_DESTROY(wrapper_of_##type,&pool->array);\
    pool->next_free = 0;\
    pool->free = 0;\
}\
type* pool_of_##type##_get(pool_of_##type* pool,size_t index){\
    wrapper_of_##type* wrapper = ARRAY_GET(wrapper_of_##type,&pool->array,index);\
    if(wrapper && wrapper->alive){\
        return &wrapper->item;\
    }\
    return NULL;\
}\
void pool_of_##type##_free(pool_of_##type* pool,size_t index){\
    if(pool->array.size > index){\
        pool->array.array[index].alive = 0;\
        pool->array.array[index].next_free = pool->next_free;\
        pool->next_free = index;\
        pool->free++;\
    }\
}\
type* pool_of_##type##_next_free(pool_of_##type* pool,size_t* ptr_to_index){\
    type* result = NULL;\
    if(pool->free > 0){\
        if(ptr_to_index != NULL)\
            *ptr_to_index = pool->next_free;\
        pool->array.array[pool->next_free].alive = 1;\
        result = &pool->array.array[pool->next_free].item;\
        pool->next_free = pool->array.array[pool->next_free].next_free;\
        pool->free--;\
        return result;\
    }else{\
        return NULL;\
    }\
}\
type* pool_of_##type##_next(pool_of_##type* pool){\
    while(pool->counter < pool->array.size){\
        if(pool->array.array[pool->counter].alive){\
            pool->counter++;\
            return &pool->array.array[pool->counter-1].item;\
        }\
        pool->counter++;\
    }\
    pool->counter = 0;\
    return NULL;\
}\

#endif

