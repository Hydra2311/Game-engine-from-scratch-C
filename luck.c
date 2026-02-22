#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    int i;
    int resi,result,greatflag = TRUE,flag = TRUE;
    int firstace = TRUE,chosen1 = FALSE,chosen11 = FALSE,card,firstcard,hpoints=0,ppoints=0;
    char c,r;
    while (greatflag)
    {
        fprintf(stdout,"1.Dice Roll 2.Blackjack 3.Quit: ");
        scanf("%d",&resi);
        while((c = getchar()) != '\n');
        switch (resi)
        {
            case 1: /*Gives the option of 6 different dice*/
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
            case 2: /*Main Blackjack game loop*/
            {
                /*House's/Computer's turn*/

                firstcard = drawcard(Blackjack,sizeof(Blackjack));
                printf("Hidden\n\n");
                if (card != 12)
                    hpoints += Blackjack[firstcard].points;
                else
                    /*Function ace is used to handle drawing an ace based on different circumstances*/
                    /*such as, if it's the first ace drawn and if a 1 has been already chosen.*/
                    hpoints = ace(&firstace,hpoints,&chosen1);                
                while (flag)
                {
                    card = drawcard(Blackjack,sizeof(Blackjack));
                    printf("%s\n\n",Blackjack[card].card);
                    if (card != 12)
                        hpoints += Blackjack[card].points;
                    else
                        hpoints = ace(&firstace,hpoints,&chosen1);
                    if ((hpoints >= 15) && (hpoints < 21))
                    {
                        printf("The House is done.\nPlayer's turn.\n");
                        flag = FALSE;
                    }
                    else if (hpoints == 21)
                    {
                        printf("The House has BLACKJACK!!!\nThe only to survive is with a BLACKJACK of your own!\n");
                        flag = FALSE;
                    }
                    else if (hpoints > 21)
                    {
                        printf("The House has over 21.\nThe player WINS!!!\n");
                        flag = FALSE;
                    }
                }
                flag = TRUE;
                firstace = TRUE;
                chosen1 = FALSE;
                if (hpoints > 21)
                {
                    hpoints = 0;
                    break;
                }
                usleep(200000);

                /*Player's turn*/

                printf("Your starting hand\n");
                /*Draws automatically 2 cards for the player*/
                for(i=0;i<2;i++)
                {
                    card = drawcard(Blackjack,sizeof(Blackjack));
                    printf("%s\n",Blackjack[card].card);
                    if (card != 12)
                        ppoints += Blackjack[card].points;
                    else
                    {
                        if (firstace)
                        {
                            printf("Choose 1 or 11: ");
                            scanf("%d",&resi);
                            while ((c = getchar()) != '\n');
                            if (resi == 1)
                            {
                                ppoints += 1;
                                chosen1 = TRUE;
                            }
                            else if (resi == 11)
                            {
                                ppoints += 11;
                                chosen11 = TRUE;
                            }
                        }
                        else
                        {
                            if (chosen11 == TRUE)
                                ppoints += 1;
                            else if (chosen1 == TRUE)
                                ppoints += 11;
                        }
                    }
                    usleep(100000);
                }
                while (flag)
                {
                    if (ppoints > 21)
                    {
                        printf("Over 21. You LOSE!!!\n");
                        break;
                    }
                    else if (ppoints == 21)
                    {
                        printf("BLACKJACK!!!\n");
                        if (hpoints == 21)
                            printf("Sadly it's a TIE\n");
                        else
                            printf("You WIN!!!\n");
                        break;
                    }
                    printf("Your total points are %d\n",ppoints);
                    printf("Do you wish to draw again?[y/n] ");
                    r = getchar();
                    while ((c = getchar()) != '\n');
                    switch (r)
                    {
                        case 'y': case 'Y': 
                        {
                            card = drawcard(Blackjack,sizeof(Blackjack));
                            ppoints += Blackjack[card].points;
                            printf("%s\n",Blackjack[card].card);  
                            break;  
                        }
                        case 'n': case 'N':
                        {
                            printf("Revealing the Hidden : %s\n",Blackjack[firstcard].card);
                            if (ppoints > hpoints)
                                printf("You WIN!!!\n");
                            else if (ppoints <= hpoints)
                                printf("you LOSE!!!\n");
                            flag = FALSE;
                            break;
                        }
                        default:
                        {
                            printf("Not valid");
                            break;
                        }
                    }
                }
                ppoints = 0;
                hpoints = 0;
                
                firstace = TRUE;
                chosen11 = FALSE;
                chosen1 = FALSE;
                flag = TRUE;
                break;
            }
            case 3:
            {
                fprintf(stdout,"Thank you for playing our game\n");
                greatflag = FALSE;
                break;
            }
            default:
            {
                fprintf(stdout,"Invalid choice given. Please choose again.\n");
            }
        }
    }
    return 0;
}

