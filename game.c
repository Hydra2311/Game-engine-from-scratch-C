#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

int main()
{
	const char *Races[] = {"Dwarf","Human","Orc"};
	char **map,buf[200],c;
	int x=5,y=30,i,rch,spawnpoint,j;
	srand(time(NULL));
	spawnpoint = rand()%(y+1);

	map = createmap(x,y);

	fprintf(stdout,"Choose a name: ");
	fgets(buf,30,stdin);
	buf[strcspn(buf,"\n")] = '\0';

	fprintf(stdout,"Choose race(0.Dwarf,1.Human,2.Orc): ");
	scanf("%d",&rch);
	while((c = getchar()) != '\n');

	Char char1 = createchar(buf,rch);

	fprintf(stdout,"Your champion has been created\n");
	map[x-2][spawnpoint] = char1.race; 

	fprintf(stdout,"His name is %s\n", char1.name);
	fprintf(stdout,"His race is %s\n", Races[rch]);
	fprintf(stdout,"His hp is %d\n", char1.hp);

	for(i=0;i<x;i++)
	{
		if(i < (x-2))
			fprintf(stdout,"\n");
		else if(i == (x-2))
			for(j=0;j<y;j++)
			{
				if (j == spawnpoint)
				{
					fprintf(stdout,"%c\n",map[i][spawnpoint]);
					break;
				}
				else
					fprintf(stdout," ");
			}
		else
			fprintf(stdout,"%s\n",map[i]);
	}

	return 0;
}
