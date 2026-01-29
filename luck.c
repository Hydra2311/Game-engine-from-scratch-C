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
    int resi,result;
    char c;
    while (TRUE)
    {
        fprintf(stdout,"1.Dice Roll 2.Blackjack 3.Quit: ");
        scanf("%d",&resi);
        while((c = getchar()) != '\n');
        switch (resi)
        {
            case 1:
            {
                fprintf(stdout,"1.D4,2.D6,3.D8,4.D10,5.D12,6.D20: ");
                scanf("%d",&resi);
                while((c = getchar()) != '\n');
                switch (resi)
                {
                    case 1:
                    {
                        diceroll(4,&result);
                        break;
                    }
                    case 2:
                    {
                        diceroll(6,&result);
                        break;
                    }
                    case 3:
                    {
                        diceroll(8,&result);
                        break;
                    }
                    case 4:
                    {
                        diceroll(10,&result);
                        break;
                    }
                    case 5:
                    {
                        diceroll(12,&result);
                        break;
                    }
                    case 6:
                    {
                        diceroll(20,&result);
                        break;
                    }
                    default:
                    {
                        fprintf(stderr,"Not valid dice\n");
                    }
                }
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

