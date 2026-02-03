#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "engine.h" 

/*Unity framework from GitHub : Unit tests for engine.c*/

void setUp()
{

}

void tearDown()
{

}

void test_charmove()
{
    /*Testing movement close and on the borders*/

    int output = charmove(30,28,'>');
    TEST_ASSERT_EQUAL(29,output);
    output = charmove(30,29,'>');
    TEST_ASSERT_EQUAL(29,output);
    output = charmove(30,1,'<');
    TEST_ASSERT_EQUAL(0,output);
    output = charmove(30,0,'<');
    TEST_ASSERT_EQUAL(0,output);
}

void test_form()
{
    /*Testing error codes: 0 = Username Error, 1 = Password Error*/

    Form baseform,usererror,passerror;
    strcpy(baseform.username,"User1");
    strcpy(baseform.password,"Pass1");
    strcpy(usererror.username,"user1");
    strcpy(usererror.password,"Pass1");
    strcpy(passerror.username,"User1");
    strcpy(passerror.password,"pass1");

    int output1 = checkform(baseform,usererror);
    int output2 = checkform(baseform,passerror);

    TEST_ASSERT_EQUAL(output1,0);
    TEST_ASSERT_EQUAL(output2,1);
}

void test_spawn()
{
    /*Testing if the spawn point is inside the x-axis*/

    int output = randspawn(30);

    TEST_ASSERT_LESS_THAN(30,output);
    TEST_ASSERT_GREATER_THAN(-1,output);
}

int main (void)
{
    printf("\n");
    UNITY_BEGIN();

    RUN_TEST(test_charmove);
    RUN_TEST(test_form);
    RUN_TEST(test_spawn);

    UNITY_END();
    return 0;
}