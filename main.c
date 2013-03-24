#include <stdio.h>
#include <stdlib.h>
#include "include/oDAO.h"
#include "lib/LinkedList.h"
//#include <ncurses.h>

#define PASS_SIZE 64

#define ECHO_ON 1
#define ECHO_OFF 0
#define BACK_SPACE 127


char* my_getpass(int echostate)
{
	char c;
	int i = 0;
	char* pass;
	
	pass = malloc(sizeof(char) * PASS_SIZE);

	noecho();
	cbreak();
	
	while(i<PASS_SIZE && (c=getch()) != '\n')
	{
		if(c == BACK_SPACE) 
		{
			if(i > 0) 
			{
				i--;
				if(echostate == ECHO_ON)
					printw("\b \b");	
			}
		}
		else {
			pass[i++] = c;
			if(echostate == ECHO_ON)
				printw("*");
		}
	}
	pass[i] = '\0';
	echo();
	nocbreak();
	printw("\n");
	return pass;
}

int main()
{
	char *pass, *stmt;
	char c;
	pDB_values values;
	pDAOplan plan;
	
	initscr();	
	printw("Enter password: ");
	refresh();
	pass = my_getpass(ECHO_OFF);
	
	values = malloc(sizeof(DB_values_t));
	values->user = "root";
	values->pwd = pass;
	values->host = "localhost";
	//stmt = "DROP DATABASE testDB";
	//executeDDL(values, &stmt, 1);
	
	plan = registerDAO("DVD");
	daoplan_add_int(plan, "length");
	daoplan_add_int(plan, "anzschauspieler");
	daoplan_add_string(plan, "title", 255);
	generate(plan);
	getch();
	endwin();
	return 0;
}
