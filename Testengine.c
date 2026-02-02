#include <stdio.h>
#include "unity.h"
#include "engine.h" 

void setUp()
{

}

void tearDown()
{

}

void test_charmove()
{
    int output = charmove(30,28,'>');
    TEST_ASSERT_EQUAL(29,output);
    output = charmove(30,29,'>');
    TEST_ASSERT_EQUAL(29,output);
    output = charmove(30,1,'<');
    TEST_ASSERT_EQUAL(0,output);
    output = charmove(30,0,'<');
    TEST_ASSERT_EQUAL(0,output);
}

int main (void)
{
    UNITY_BEGIN();

    RUN_TEST(test_charmove);

    UNITY_END();
    return 0;
}