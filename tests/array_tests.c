#include <tester.h>
#include "../array.h"
ARRAY_DEC(int)
ARRAY_DEF(int)
ARRAY(int) array;
ENVIROMENT_SETUP{
    array = ARRAY_CREATE(int,10);
    ARRAY_ADD(int,&array,5);
}
ENVIROMENT_CLEANUP{
    ARRAY_DESTROY(int,&array);
}
TESTS
    UNIT_TEST_START("properties")
        ASSERT(array.size == 1);
        ASSERT(array.capacity == 10);
    UNIT_TEST_END
    UNIT_TEST_START("adding")
        ARRAY_ADD(int,&array,7);
        ASSERT(array.size == 2);
        ASSERT(array.array[1] == 7);
    UNIT_TEST_END
    UNIT_TEST_START("getting")
        ASSERT(*ARRAY_GET(int,&array,0) == 5);
    UNIT_TEST_END
    UNIT_TEST_START("insert")
        ARRAY_INSERT(int,&array,5,5);
        ASSERT(*ARRAY_GET(int,&array,5) == 5);
    UNIT_TEST_END
    UNIT_TEST_START("destroy")
        ARRAY(int) array2 =  ARRAY_CREATE(int,5);
        ARRAY_DESTROY(int,&array2);
        ASSERT(array2.size == 0);
        ASSERT(array2.capacity == 0);
        ASSERT(array2.array == NULL);
    UNIT_TEST_END
    UNIT_TEST_START("getting and changing")
        *ARRAY_GET(int,&array,0) = 3;
        ASSERT(*ARRAY_GET(int,&array,0) == 3);
    UNIT_TEST_END
END_TESTS
