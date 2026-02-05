#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

char ** createmap(int x,int y) /*the dimensions of the map you wish to create*/
{	
	char **map;
	int i,j;
	map = (char **)malloc(y * sizeof(char *)); /*dynamic array of (char **)*/
	if(map == NULL)
	{
		fprintf(stderr,"Couldn't allocate memory\n");
		exit(-1);
	}
	for(i=0;i<y;i++)
	{
		map[i] = (char *)malloc((x+1) * sizeof(char)); /*size creation for array of strings*/
		if(map[i] == NULL)
		{
			fprintf(stderr,"Couldn't allocate memory\n");
			exit(-2);
		}
	}
	for(i=0; i<y; i++) /*cleaning the allocated memory*/
	{	
        for(j=0; j<x; j++) 
		{
            map[i][j] = ' '; 
        }
        map[i][x] = '\0';
    }
	for(i=0;i<x+1;i++)
	{
		if (i < x)
			map[y-1][i] = '_'; /*Creating the floor*/
		else if(i == x)
			map[y-1][i] = '\0';
	}

	return map;
}

Char createchar(char name[],int choice) /*Character stat block*/
{
	Char char1;
	strcpy(char1.name,name);
	char1.hp = MAX_HP;
	if (choice == Dwarf) /*based on the struct in engine.h*/
		char1.race = 'i';
	else if (choice == Human)
		char1.race = 'I';
	else if (choice == Orc)
		char1.race = 'M';

	return char1;
}

void displaymap(char **map,int x,int y,int curpos) /*Function to display the map*/
{
	int i,j;

	for(i=0;i<y;i++)
	{
		if(i <= (y-2))
		{
			for(j=0;j<x;j++)
			{
				if(j<x-1)
				{
					fprintf(stdout,"%c",map[i][j]);
				}
				else
				{
					fprintf(stdout,"%c\n",map[i][j]);
				}
			}
		}
		else
		{
			fprintf(stdout,"%s\n",map[i]);
		}
	}
}

int charmove(int x,int currentposition,char direction) /*Character movement < or >*/
{
	if(direction == '>')
	{
		if (currentposition<x-1) /*Moving the position of the character in the array*/
			currentposition++;
	}
	else if(direction == '<')
	{
		if (currentposition>0)
			currentposition--;
	} 

	return currentposition;
}

void charshootr(char **map,int x,int y,int curpos) /*Function to shoot a bullet to the right*/
{
	/*Checks if character is on the border, if not it creates and moves a bullet thoughout*/
	/*the array. It continues until either it hits a border or another thing inside the array.*/
	int i,base = y-2;

	if(curpos != (x-1))
	{	
		for(i=0;i<x-1-curpos;i++)
		{
			if (map[base][curpos+i+1] == ' ')
			{
				if (map[base][curpos+i] == '-')
					map[base][curpos+i] = ' ';
				map[base][curpos+i+1] = '-';
			}
			else
			{
				if (map[base][curpos+i] == '-')
					map[base][curpos+i] = ' ';
				break;
			}
			displaymap(map,x,y,curpos);
			usleep(85000);
			system("clear");
		}

		if (map[base][x-1] == '-')
			map[base][x-1] = ' ';
		displaymap(map,x,y,curpos);
		system("clear");
	}
	displaymap(map,x,y,curpos);
}

void charshootl(char **map,int x,int y,int curpos) /*Function to shoot a bullet to the left*/
{
	/*It performs the same way as charshootr*/
	int i=curpos,base = y-2;

	if(curpos > 0)
	{	
		while(i>-1)
		{
			if (map[base][i-1] == ' ')
			{
				if (map[base][i] == '-')
					map[base][i] = ' ';
				map[base][i-1] = '-';
			}
			else
			{
				if (map[base][i] == '-')
					map[base][i] = ' ';
				break;
			}
			displaymap(map,x,y,curpos);
			usleep(85000);
			system("clear");
			i--;
		}
		if (map[base][0] == '-')
			map[base][0] = ' ';
		displaymap(map,x,y,curpos);
		system("clear");
	}
	displaymap(map,x,y,curpos);
}

Form fillform(char user[],char pass[]) /*Fills register/login form*/
{
	Form form1;

	strcpy(form1.username,user);
	strcpy(form1.password,pass);

	return form1;
}

int checkform(Form checkform,Form forcheck) 
{
	/*compares the register form with the login form and returns a type casted*/
	/*version of the response*/
	int response;

	if(strcmp(checkform.username,forcheck.username) == 0)
	{
		if(strcmp(checkform.password,forcheck.password) == 0)
			response = 2;
		else
			response = 1;
	}
	else
	{
		response = 0;
	}

	return ((Checklogin)response);
}

void jump(char **map,int x,int y,int curpos,int height) /*Function to jump*/
{
	/*Moves the character first up a set amount of blocks given by the height*/
	/*variable and then it returns to its original position.*/
	int i,curry,base = y-2,peak;
	char temp;

	if (height > base)
	{
		fprintf(stderr,"Height too low for this jump");
		displaymap(map,x,y,curpos);
	}
	else
	{
		for(i=0;i<height;i++)
		{
			curry = base - (i+1);

			temp = map[base-i][curpos];
			map[base-i][curpos] = map[curry][curpos];
			map[curry][curpos] = temp;
			
			displaymap(map,x,y,curpos);
			usleep(110000);
			system("clear");
		}
		peak = base - height;
		for(i=0;i<height;i++)
		{
			curry = peak + (i+1);

			temp = map[peak+i][curpos];
			map[peak+i][curpos] = map[curry][curpos];
			map[curry][curpos] = temp;

			displaymap(map,x,y,curpos);
			usleep(180000);
			system("clear");
		}
		displaymap(map,x,y,curpos);
	}
}

Enemy createene(int choice,char **map,int x,int y) /*Enemy stat block*/
{
	/*Based on the struct in engine.h*/
	Enemy baseenemy;
	int enepos,att = 0,maxatt = 75;
	srand(time(NULL));
	enepos = rand()%x;
	int base = y-2;

	while(map[base][enepos] != ' ' && att < maxatt)
	{
		enepos = rand()%x;
		att++;
	}

	if (choice == Goblin)
	{
		baseenemy.race = 'g';
		baseenemy.hp = 2;
		baseenemy.power = 1;
		baseenemy.enpos = enepos;
	}
	else if (choice == Hobgoblin)
	{
		baseenemy.race = 'H';
		baseenemy.hp = 4;
		baseenemy.power = 2;
		baseenemy.enpos = enepos;
	}

	return baseenemy;
}

int randspawn(int x) /*Character spawning based on map length*/
{
	srand(time(NULL));

	return (rand()%x);
}

void diceroll(int lim,int *result)
{
	/*Prints random numbers based on the var amount, so that it looks like*/
	/*the dice is actually rolling.*/
	srand(time(NULL));
	int amount=20,i,cur_val;

    for(i = 0; i < amount; i++)
    {
        int delay = 50000 + (i * 1000); 

        cur_val = (rand()%lim) + 1;
        
        printf("\rRolling: %d   ", cur_val);
		fflush(stdout);
        
        usleep(delay);
    }

    *result = cur_val;
    printf("\nFinal Result: %d\n", *result);
}

int drawcard(Deck Jack[],int size) /*Randomly draws card based on the size of the deck*/
{
	srand(time(NULL));
	int amount = (size/sizeof(Jack[0]));

	return (rand()%amount + 1);
}

int ace(int *firstace,int hpoints,int *chosen1) /*Calling by reference using pointers*/
{
	/*Decision making for the "house" when it draws an ace based on, the amount of aces*/
	/*it has, if it's the first ace drawn and the amount of points it already has.*/

	if (*(firstace))
    {
        if ((hpoints <= 10) && (hpoints >= 5))
		{
            hpoints += 11;
		}
        else
        {
            hpoints += 1;
            *(chosen1) = TRUE;
        }
		*(firstace) = FALSE;
    }
    else
    {
        if (*(chosen1))
            hpoints += 11;
        else
            hpoints += 1;
    }

	return hpoints;
}