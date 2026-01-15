#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** createmap(int x,int y) /*the dimensions of the map you wish to create*/
{
	char **map;
	int i;
	map = (char **)malloc(x * sizeof(char *)); /*dynamic array of (char **)*/
	if(map == NULL)
	{
		fprintf(stderr,"Couldn't allocate memory\n");
		exit(-1);
	}
	for(i=0;i<x;i++)
	{
		map[i] = (char *)malloc((y+1) * sizeof(char)); /*size creation for array of strings*/
		if(map[i] == NULL)
		{
			fprintf(stderr,"Couldn't allocate memory\n");
			exit(-2);
		}
	}
	for(i=0;i<y+1;i++)
	{
		if (i < y)
			map[x-1][i] = '_'; /*Creating the floor*/
		else if(i == y)
			map[x-1][i] = '\0';
	}

	return map;
}

Char createchar(char name[],int choice) /*Character stat block*/
{
	Char char1;
	strcpy(char1.name,name);
	char1.hp = MAX_HP;
	if (choice == Dwarf)
		char1.race = 'i';
	else if (choice == Human)
		char1.race = 'I';
	else if (choice == Orc)
		char1.race = 'M';

	return char1;
}