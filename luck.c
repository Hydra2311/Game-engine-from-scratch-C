#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int main()
{
    Blackjack Cards[] = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
        {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10},
        {"Jack", 10}, {"Queen", 10}, {"King", 10}, {"Ace", 1} 
    };
    int acecount=0;
    int resi;
    char c;
    while (TRUE)
    {
        fprintf(stdout,"1.Dice Roll 2.Blackjack 3.Quit");
        scanf("%d",&resi);
        while((c = getchar()) != NULL);
        switch (resi)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                fprintf(stdout,"Thank you for playing our game\n");
                exit(1);
            }
        }
    }

    return 0;
}

