#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int main()
{
    Deck Blackjack[] = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
        {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10},
        {"Jack", 10}, {"Queen", 10}, {"King", 10}, {"Ace", 1} 
    };
    int acecount=0;
    int resi,result;
    int firstace = TRUE,chosen1 = FALSE,card,hpoints=0,ppoints=0,pulls=0;
    char housecards[5][10],playercards[5][10];
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
                while (hpoints <= 21)
                {
                    card = drawcard(Blackjack,sizeof(Blackjack));
                    if(card != 13)
                    {
                        hpoints += Blackjack[card].points;
                    }
                    else
                    {
                        hpoints += ace(&firstace,hpoints,&chosen1);
                    }
                }
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

