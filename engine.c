#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void charshoot(char **map,int x,int y,int curpos) /*Function to shoot a bullet*/
{
	/*Checks if character is on the border, if not it creates and moves a bullet thoughout*/
	/*the array. It continues until either it hits a border or another thing inside the array.*/
	int i;

	if(curpos != (x-1))
	{	
		for(i=0;i<x-1-curpos;i++)
		{
			if (map[y-2][curpos+i+1] == ' ')
			{
				if (map[y-2][curpos+i] == '-')
					map[y-2][curpos+i] = ' ';
				map[y-2][curpos+i+1] = '-';
			}
			else
			{
				map[y-2][curpos+i] = ' ';
				break;
			}
			displaymap(map,x,y,curpos);
			usleep(85000);
			system("clear");
		}
		map[y-2][x-1] = ' ';
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
	/*var and then it returns to its original position.*/
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