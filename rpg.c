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
	int rch,erch,enemycount=0,enemycapacity=5;
	int i,j,k;
	int greatflag = TRUE,flag = FALSE,check,maxtries = 3;
	int curpos,next_pos,enepos,base,close_ene_r=-1,close_ene_l=-1;
	FILE *fpa,*fpr;
	Form baseform,forcheck;
	Enemy *enemies;
	Char char1;

	/*If the logindata.txt is empty, asks the user to register with username and password.*/
	/*If it isn't, asks the user to login and compares the data given with the registered data.*/
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
				fprintf(stderr,"Failed to login\n");
				exit(-5);
			}
		}
	}
	/*Character and map creation*/

	map = createmap(x,y);
	curpos = randspawn(x);
	base = y-2;

	fprintf(stdout,"Choose a name: ");
	fgets(buf,30,stdin);
	buf[strcspn(buf,"\n")] = '\0';

	fprintf(stdout,"Choose race(0.Dwarf,1.Human,2.Orc): ");
	scanf("%d",&rch);
	while((c = getchar()) != '\n');

	char1 = createchar(buf,rch);

	fprintf(stdout,"Your champion has been created\n");
	map[base][curpos] = char1.race; 

	fprintf(stdout,"His name is %s\n", char1.name);
	fprintf(stdout,"His race is %s\n", Races[rch]);
	fprintf(stdout,"His hp is %d\n", char1.hp);

	displaymap(map,x,y,curpos);

	while (greatflag)
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
				/*If there are no enemies, it allocates memory for (int capacity) enemies.*/
				/*Otherwise if the enemy count is about to surpass the capacity it*/
				/*reallocates more memory for the array of enemies.*/
				if(enemycount == 0)
				{
					enemies = (Enemy *)malloc(enemycapacity * sizeof(Enemy));
					if (enemies == NULL)
					{
						fprintf(stderr,"Couldn't allocate memory\n");
						exit(-7);
					}
				}
				if(enemycount >= enemycapacity)
				{
					Enemy *tempenemies;
					enemycapacity += 5;
					tempenemies = (Enemy *)realloc(enemies,(enemycapacity * sizeof(Enemy)));
					if (tempenemies == NULL)
					{
						fprintf(stderr,"Couldn't allocate memory\n");
						exit(-8);						
					}
					enemies = tempenemies;
				}
				enemies[enemycount] = createene(erch,map,x,y);
				fprintf(stdout,"Your %s has been created\n",EnRaces[erch]);

				map[base][enemies[enemycount].enpos] = enemies[enemycount].race;
				displaymap(map,x,y,curpos);
				enemycount++;
				break;
			}
			case '*':
			{
				fprintf(stdout,"Thank you for using our app\n");
				/*Freeing all the memory that has been allocated manually*/

				for(i=0;i<y;i++)
				{
					free(map[i]);
				}
				free(map);

				if (enemycount>0)
				{
					free(enemies);
				}
				greatflag = FALSE;
				break;
			}
			default:
			{
				fprintf(stdout,"Invalid choice given.");
			}
		}
		/*Dealing damage based on the direction of the shot and the closest*/
		/*enemy to that direction.*/
		if (response == 'R')
		{
			if (close_ene_r == -1)
			{
				for(i=curpos+1;i<x;i++)
				{
					if(map[base][i] == 'H' || map[base][i] == 'g')
					{
						close_ene_r = i;
						break;
					}
				}
			}
			if((enemycount>0) && (close_ene_r != -1))
			{
				for(i=0;i<enemycount;i++)
				{
					if(enemies[i].enpos == close_ene_r)
					{
						enemies[i].hp--;
						if (enemies[i].hp <= 0)
						{
							map[base][enemies[i].enpos] = ' ';
							for(k = i; k < enemycount - 1; k++) 
                    		{
                        		enemies[k] = enemies[k+1];
                    		}
							enemycount--;
							close_ene_r = -1;
						}
						break;
					}
				}
			}
		}
		if (response == 'L')
		{
			if (close_ene_l == -1)
			{
				for(i=curpos-1;i>-1;i--)
				{
					if(map[base][i] == 'H' || map[base][i] == 'g')
					{
						close_ene_l = i;
						break;
					}
				}
			}
			if((enemycount>0) && (close_ene_l != -1))
			{
				for(i=0;i<enemycount;i++)
				{
					if(enemies[i].enpos == close_ene_l)
					{
						enemies[i].hp--;
						if (enemies[i].hp <= 0)
						{
							map[base][enemies[i].enpos] = ' ';
							for(k = i; k < enemycount - 1; k++) 
                    		{
                        		enemies[k] = enemies[k+1];
                    		}
							enemycount--;
							close_ene_l = -1;
						}
						break;
					}
				}
			}
		}
	}

	return 0;
}
