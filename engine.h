#ifndef ENGINE_H
#define ENGINE_H

#define GRAVITY 1
#define MAX_HP 10

typedef enum {Dwarf,Human,Orc} Race; /*For character stat block*/

extern const char *Races[]; /*Global variable for Races*/

typedef struct /*Character stats*/
{
	char name[30];
	char race;
    int hp;
}Char;

char ** createmap(int , int); /*Creates map with given dimensions*/
Char createchar(char[] ,int ); /*Creates a stat block*/
int charmove(int ,int ,char ); /*Movement to the right or left*/
void displaymap(char **,int ,int ,int ); /*Prints map to the screen*/
void charshoot(char **,int ,int ,int ); /*Shoots bullet*/

#endif
