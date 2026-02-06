#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "engine.h" 
#define TRUE 1
#define FALSE 0

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

void test_draw()
{
    /*Testing if the card drawn is in the limits of the deck*/

    Deck Blackjack[] = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
        {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10},
        {"Jack", 10}, {"Queen", 10}, {"King", 10}, {"Ace", 1} 
    };

    int output = drawcard(Blackjack,sizeof(Blackjack));

    TEST_ASSERT_LESS_THAN(13,output);
    TEST_ASSERT_GREATER_THAN(-1,output);
}

void test_ace()
{
    /*Testing all the edge cases for the decision making of the "house" when*/
    /*it draws an ace*/

    int true = TRUE,false = FALSE;
    int output1 = ace(&true,7,&false);

    true = TRUE; false = FALSE;
    int output2 = ace(&true,12,&false);

    true = TRUE; false = FALSE;
    int output3 = ace(&true,3,&false);

    true = TRUE; false = FALSE;
    int output4 = ace(&false,10,&true);

    true = TRUE; false = FALSE;
    int output5 = ace(&false,10,&false);

    TEST_ASSERT_EQUAL(output1,18);
    TEST_ASSERT_EQUAL(output2,13);
    TEST_ASSERT_EQUAL(output3,4);
    TEST_ASSERT_EQUAL(output4,21);
    TEST_ASSERT_EQUAL(output5,11);        
}

int main (void)
{
    printf("\n");
    UNITY_BEGIN();

    RUN_TEST(test_charmove);
    RUN_TEST(test_form);
    RUN_TEST(test_spawn);
    RUN_TEST(test_draw);
    RUN_TEST(test_ace);

    return UNITY_END();
}