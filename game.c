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
	char **map,buf[200],c,direction,temp_pos;
	int x=30,y=5,i,rch,curpos,j,next_pos;
	srand(time(NULL));
	curpos = rand()%x;

	map = createmap(x,y);

	fprintf(stdout,"Choose a name: ");
	fgets(buf,30,stdin);
	buf[strcspn(buf,"\n")] = '\0';

	fprintf(stdout,"Choose race(0.Dwarf,1.Human,2.Orc): ");
	scanf("%d",&rch);
	while((c = getchar()) != '\n');

	Char char1 = createchar(buf,rch);

	fprintf(stdout,"Your champion has been created\n");
	map[y-2][curpos] = char1.race; 

	fprintf(stdout,"His name is %s\n", char1.name);
	fprintf(stdout,"His race is %s\n", Races[rch]);
	fprintf(stdout,"His hp is %d\n", char1.hp);

	displaymap(map,x,y,curpos);

	while (TRUE)
	{
		fprintf(stdout,"Right > Left < Exit *\n");
		direction = getchar();
		while((c = getchar()) != '\n');

		if (direction != '*')
		{
			next_pos = charmove(x,curpos,direction);

			temp_pos = map[y-2][curpos];
			map[y-2][curpos] = map[y-2][next_pos];
			map[y-2][next_pos] = temp_pos;

			curpos = next_pos;


			displaymap(map,x,y,curpos);
		}
		else
		{
			fprintf(stdout,"Thank you for using our app\n");
			exit(1);
		}
	}

	return 0;
}
