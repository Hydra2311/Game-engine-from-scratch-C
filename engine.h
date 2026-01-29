#ifndef ENGINE_H
#define ENGINE_H

#define MAX_HP 10

typedef enum {Dwarf,Human,Orc} Race; /*For character stat block*/
typedef enum {IncorrectUsername,IncorrectPassword,Correct} Checklogin; /*For login checking*/
typedef enum {Goblin,Hobgoblin} EnRace; /*For enemy stat block*/
extern const char *Races[]; /*Global variable for Races*/
extern const char *Checklogins[]; /*Global variable for login checking*/
extern const char *EnRaces[]; /*Global variable for Enemy Races*/

typedef struct /*Enemy stats*/
{
	char race;
	int hp;
	int power;
}Enemy;

typedef struct /*Character stats*/
{
	char name[30];
	char race;
    int hp;
}Char;

typedef struct /*Login/Register form*/
{
	char username[30];
	char password[30];
}Form;

typedef struct
{
	char card[20];
	int points;
}Blackjack;

char ** createmap(int , int); /*Creates map with given dimensions*/
Char createchar(char[] ,int ); /*Creates a stat block*/
int charmove(int ,int ,char ); /*Movement to the right or left*/
void displaymap(char **,int ,int ,int ); /*Prints map to the screen*/
void charshootr(char **,int ,int ,int ); /*Shoots bullet to the right*/
void charshootl(char **,int ,int ,int ); /*Shoots bullet to the left*/
Form fillform(char[] ,char[] ); /*Puts username & password in struct*/
int checkform(Form ,Form ); /*Compares the register form with the login form*/
void jump(char **,int ,int ,int ,int ); /*Jumps based on the height given*/
Enemy createene(int ); /*Creates an enemy's stat block*/
int spawnenemy(char **,int ,int ); /*Randomly spawns an enemy on the map*/
int randspawn(int );
void diceroll(int ,int *);

#endif
