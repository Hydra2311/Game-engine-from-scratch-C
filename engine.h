#ifndef ENGINE_H
#define ENGINE_H

#define MAX_HP 10

typedef enum {Dwarf,Human,Orc} Race; /*For character stat block*/
typedef enum {IncorrectUsername,IncorrectPassword,Correct} Checklogin; /*For login checking*/
extern const char *Races[]; /*Global variable for Races*/
extern const char *Checklogins[]; /*Global variable for login checking*/

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


char ** createmap(int , int); /*Creates map with given dimensions*/
Char createchar(char[] ,int ); /*Creates a stat block*/
int charmove(int ,int ,char ); /*Movement to the right or left*/
void displaymap(char **,int ,int ,int ); /*Prints map to the screen*/
void charshoot(char **,int ,int ,int ); /*Shoots bullet*/
Form fillform(char[] ,char[] ); /*Putting username & password in struct*/
int checkform(Form ,Form ); /*Comparing the register form with the login form*/
void jump(char **,int ,int ,int ,int ); /*Jumping based on the height given*/

#endif
