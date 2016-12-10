#include <tester.h>
#include "../objectpool.h"
POOL_DEC(int)
POOL_DEF(int)
int a;
int* ptr_of_free;
POOL(int) pool;
ENVIROMENT_SETUP{
    a = 5;
    pool = POOL_CREATE(int,10);
}
ENVIROMENT_CLEANUP{
    POOL_DESTROY(int,&pool);
}
TESTS
    UNIT_TEST_START("properties")
        ASSERT(pool.next_free == 0);
        ASSERT(pool.free == 0);
        ASSERT(pool.array.capacity == 10); //check if the array is free
    UNIT_TEST_END
    UNIT_TEST_START("get next free empty")
        ptr_of_free = &a;
        ptr_of_free = POOL_NEXT_FREE(int,&pool,NULL);
        ASSERT(ptr_of_free == NULL);
    UNIT_TEST_END
    UNIT_TEST_START("adding to top")
        POOL_ADD(int,&pool,a);
        ASSERT(pool.array.array[0].item == 5);
        ASSERT(pool.array.array[0].next_free == 1);
        ASSERT(pool.next_free == 1);
    UNIT_TEST_END
    UNIT_TEST_START("deleting")
        POOL_ADD(int,&pool,a);
        POOL_FREE(int,&pool,0);
        ASSERT(pool.next_free == 0);
        ASSERT(pool.free == 1);
        ASSERT(pool.array.array[0].next_free == 1);
    UNIT_TEST_END
    UNIT_TEST_START("get")
        POOL_ADD(int,&pool,a);
        ASSERT(*POOL_GET(int,&pool,0) == 5);
    UNIT_TEST_END
    UNIT_TEST_START("recyling")
        ptr_of_free = NULL;
        POOL_ADD(int,&pool,a);
        POOL_ADD(int,&pool,3);
        POOL_ADD(int,&pool,7);
        POOL_ADD(int,&pool,8);
        POOL_ADD(int,&pool,9);
        POOL_ADD(int,&pool,1);
        POOL_FREE(int,&pool,2);
        POOL_FREE(int,&pool,4);
        size_t index = 0;
        ptr_of_free = POOL_NEXT_FREE(int,&pool,&index);
        ASSERT(ptr_of_free != NULL);
        ASSERT(*ptr_of_free == 9);
        ASSERT(index == 4);
        *ptr_of_free = 5;
        ASSERT(*POOL_GET(int,&pool,index) == 5);
        ptr_of_free = POOL_NEXT_FREE(int,&pool,&index);
        ASSERT(ptr_of_free != NULL);
        ASSERT(*ptr_of_free == 7);
        ASSERT(index == 2);
    UNIT_TEST_END
    UNIT_TEST_START("iterating")
        int a = 5;
        POOL_ADD(int,&pool,a);
        int b = 6;
        POOL_ADD(int,&pool,b);
        int c = 7;
        POOL_ADD(int,&pool,c);
        int i = 0;
        int* next = NULL;
        while((next = POOL_NEXT(int,&pool))){
            if(i == 1){
                ASSERT(*next == 6);
            }
            i++;
        }
    UNIT_TEST_END
END_TESTS
