#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define HEIGHT 2

int main()
{
	const char *Races[] = {"Dwarf","Human","Orc"};
	const char *Checklogins[] = {"IncorrectUsername","IncorrectPassword","Correct"};
	const char *EnRaces[] = {"Goblin","Hobgoblin"};
	char **map,buf[200],buf2[30],response,temp_pos,c;
	int x=30,y=4;
	int rch,erch;
	int i,j;
	int flag = FALSE,check,maxtries = 3;
	int curpos,next_pos,enepos,base;
	FILE *fpa,*fpr;
	Form baseform,forcheck;
	fpa = fopen("logindata.txt","a");
	fpr = fopen("logindata.txt","r");
	if (fpa == NULL)
	{
		fprintf(stderr,"Couldn't open file for writing\n");
		exit(-4);
	}
	if (fpr == NULL)
	{
		fprintf(stderr,"Couldn't open file for reading\n");
		exit(-4);
	}
	fseek(fpr,0,SEEK_END);
	if (ftell(fpr) == 0)
	{
		fseek(fpr,0,SEEK_SET);
		fprintf(stdout,"Please register here\nUsername: ");
		fgets(buf,30,stdin);
		buf[strcspn(buf,"\n")] = '\0';
		fprintf(stdout,"Password: ");
		fgets(buf2,30,stdin);
		buf2[strcspn(buf2,"\n")] = '\0';
		baseform = fillform(buf,buf2);
		fprintf(fpa,"%s\n",baseform.username);
		fprintf(fpa,"%s",baseform.password);
	}
	else
	{
		fseek(fpr,0,SEEK_SET);
		i = 0;
		while((fgets(buf2,30,fpr)) != NULL)
		{
			buf2[strcspn(buf2,"\n")] = '\0';
			if (i == 0)
				strcpy(baseform.username,buf2);
			else
				strcpy(baseform.password,buf2);
			i++;
		}
		fprintf(stdout,"Please login here\n");
		while ((flag == FALSE) && (maxtries > 0))
		{
			fprintf(stdout,"Username: ");
			fgets(buf,30,stdin);
			buf[strcspn(buf,"\n")] = '\0';
			fprintf(stdout,"Password: ");
			fgets(buf2,30,stdin);
			buf2[strcspn(buf2,"\n")] = '\0';
			forcheck = fillform(buf,buf2);
			check = checkform(baseform,forcheck);
			if (check == IncorrectUsername)
			{
				maxtries--;
				fprintf(stdout,"%s.Tries left: %d\n",Checklogins[0],maxtries);
			}
			else if(check == IncorrectPassword)
			{
				maxtries--;
				fprintf(stdout,"%s.Tries left: %d\n",Checklogins[1],maxtries);
			}
			else if(check == Correct)
			{
				fprintf(stdout,"%s\n",Checklogins[2]);
				flag = TRUE;
			}
			if(maxtries == 0)
			{
				fprintf(stdout,"Failed to login\n");
				exit(2);
			}
		}
	}

	srand(time(NULL));
	curpos = rand()%x;

	map = createmap(x,y);
	base = y-2;

	fprintf(stdout,"Choose a name: ");
	fgets(buf,30,stdin);
	buf[strcspn(buf,"\n")] = '\0';

	fprintf(stdout,"Choose race(0.Dwarf,1.Human,2.Orc): ");
	scanf("%d",&rch);
	while((c = getchar()) != '\n');

	Char char1 = createchar(buf,rch);

	fprintf(stdout,"Your champion has been created\n");
	map[base][curpos] = char1.race; 

	fprintf(stdout,"His name is %s\n", char1.name);
	fprintf(stdout,"His race is %s\n", Races[rch]);
	fprintf(stdout,"His hp is %d\n", char1.hp);

	displaymap(map,x,y,curpos);

	while (TRUE)
	{
		fprintf(stdout,"Right > Left < ShootRight R Shootleft L Jump ^ SpawnEnemy & Exit *\n");
		response = getchar();
		while((c = getchar()) != '\n');
		system("clear");

		switch(response)
		{
			case '<': case '>':
			{
				next_pos = charmove(x,curpos,response);
				if (map[base][next_pos] == ' ')
				{
					temp_pos = map[base][curpos];
					map[base][curpos] = map[base][next_pos];
					map[base][next_pos] = temp_pos;
					curpos = next_pos;
				}
				displaymap(map,x,y,curpos);
				break;
			}
			case 'R':
			{
				charshootr(map,x,y,curpos);
				break;
			}
			case 'L':
			{
				charshootl(map,x,y,curpos);
				break;
			}
			case '^':
			{
				jump(map,x,y,curpos,HEIGHT);
				break;
			}
			case '&':
			{
				fprintf(stdout,"Enemy race(0.Goblin,1.Hobgoblin): ");
				scanf("%d",&erch);
				while ((c = getchar()) != '\n');
				erch = (EnRace) erch;
				Enemy enemy = createene(erch);
				fprintf(stdout,"Your %s has been created\n",EnRaces[erch]);

				enepos = spawnenemy(map,x,y,curpos);
				map[base][enepos] = enemy.race;
				displaymap(map,x,y,curpos);
				break;
			}
			case '*':
			{
				fprintf(stdout,"Thank you for using our app\n");
				exit(1);
			}
		}
	}

	return 0;
}
