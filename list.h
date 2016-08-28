#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
typedef enum {false,true} bool;
typedef struct handle{
    size_t item_index;
    bool alive;
}handle;


#define LIST_ITEM(type) item_of_##type

#define LIST(type) list_of_##type

#define LIST_CREATE(type,init_cap) list_of_##type##_create(init_cap)

#define LIST_DESTROY(type,list) list_of_##type##_destroy(list)

#define LIST_REALLOC_ITEMS(type,list) list_of_##type##_reallocate_items(list)

#define LIST_REALLOC_HANDLES(type,list) list_of_##type##_reallocate_handles(list)

#define LIST_ADD(type,list,data) list_of_##type##_add(list,data)

#define LIST_GET(type,list,handle_index) list_of_##type##_get(list,handle_index)

#define LIST_DELETE(type,list,handle_index) list_of_##type##_delete(list,handle_index)

#define LIST_DEC(type)\
typedef struct LIST_ITEM(type){\
    type data;\
    size_t handle_index;\
}LIST_ITEM(type);\
typedef struct LIST(type){\
    LIST_ITEM(type)* items;\
    size_t item_capacity;\
    size_t item_size;\
    handle* handles;\
    size_t handle_capacity;\
    size_t handle_size;\
}LIST(type);\
LIST(type) list_of_##type##_create(size_t init_cap);\
void list_of_##type##_destroy(LIST(type)* list);\
void list_of_##type##_reallocate_items(LIST(type)* list);\
void list_of_##type##_reallocate_handles(LIST(type)* list);\
size_t list_of_##type##_add(LIST(type)* list,type data);\
type* list_of_##type##_get(LIST(type)* list,size_t handle_index);\
bool list_of_##type##_delete(LIST(type)* list,size_t handle_index);\

#define LIST_DEF(type)\
LIST(type) list_of_##type##_create(size_t init_cap){\
    LIST(type) output;\
    int i;\
    output.items = malloc(sizeof(LIST_ITEM(type))* init_cap);\
    output.item_capacity = init_cap;\
    output.item_size = 0;\
    output.handles = malloc(sizeof(handle)* init_cap);\
    for(i=0;i<init_cap;i++){\
        handle new_handle = {i,false};\
        output.handles[i] = new_handle;\
    }\
    output.handle_capacity = init_cap;\
    output.handle_size = 0;\
    return output;\
}\
void  list_of_##type##_destroy(LIST(type)* list){\
    free(list->items);\
    free(list->handles);\
}\
void  list_of_##type##_reallocate_items(LIST(type)* list){\
    list->item_capacity *= 2;\
    LIST_ITEM(type)* new_items = realloc(list->items,sizeof(LIST_ITEM(type))* list->item_capacity);\
    list->items = new_items;\
}\
void  list_of_##type##_reallocate_handles(LIST(type)* list){\
    list->handle_capacity *= 2;\
    handle* new_handles = realloc(list->handles,sizeof(handle)* list->handle_capacity);\
    list->handles = new_handles;\
}\
size_t list_of_##type##_add(LIST(type)* list,type data){\
    LIST_ITEM(type) new_item = {data,list->handle_size};\
    handle new_handle = {list->item_size,true};\
    if(list->item_size >= list->item_capacity){\
        LIST_REALLOC_ITEMS(type,list);\
    }\
    if(list->handle_size >= list->handle_capacity){\
        LIST_REALLOC_HANDLES(type,list);\
    }\
    list->items[list->item_size] = new_item;\
    list->handles[list->handle_size] = new_handle;\
    list->item_size++;\
    return list->handle_size++;\
}\
type* list_of_##type##_get(LIST(type)* list,size_t handle_index){\
    if(list->handles[handle_index].alive == true){\
        return &list->items[list->handles[handle_index].item_index].data;\
    }\
    return NULL;\
}\
bool list_of_##type##_delete(LIST(type)* list,size_t handle_index){\
    if(list->item_size > 0 || list->handles[handle_index].alive){\
        list->handles[handle_index].alive = false;\
        if(list->item_size > 1){\
            list->handles[list->items[list->item_size-1].handle_index].item_index = list->handles[handle_index].item_index;\
            list->items[list->handles[handle_index].item_index] = list->items[list->item_size-1];\
            list->handles[handle_index].alive = false;\
        }\
    }else{\
        return false;\
    }\
    list->item_size--;\
    return true;\
}

#endif
