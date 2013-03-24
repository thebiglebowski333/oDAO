#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <my_global.h>
#include <mysql.h>
#include <ncurses.h>
#include "include/oDAO.h"
#include "lib/LinkedList.h"

#define DDL_MAX_LENGTH 65536

char* concat(char* str1, char* str2) 
{
	char* merged;
	int len;
	int i;
	
	len = strlen(str1) + strlen(str2) + 1;
	merged = malloc(sizeof(char)*len);
	
}

int executeDDL(pDB_values values, char **stmts, int stmtcount)
{
	MYSQL conn;
	MYSQL *connection;
	int i;
	
	if(values->host == NULL)
	{
		values->host = "localhost";
	}
	
	connection = &conn;
	
	connection = mysql_init(connection);
	if(!mysql_real_connect(connection, values->host, values->user, values->pwd, values->dbname, 0, NULL, 0))
	{
		printw("%s", mysql_error(connection));
		refresh();
		getchar();
		return 1;	
	} else {
		printw("connection established\n");
		refresh();
	}
	
	for(i=0; i<stmtcount; i++) 
	{
		mysql_query(connection, stmts[i]);
		printw("%s\n", stmts[i]);
		refresh();
	}
	
	mysql_close(connection);
	return 0;
}

pDAOplan registerDAO(char* structName)
{
	pDAOplan plan;
	plinked_list list;

	plan = malloc(sizeof(DAOplan_t));
	plan->structName = structName;
	list = init_list();
	plan->fields = list;

	return plan;
}

void daoplan_add_int(pDAOplan daoplan, char* fieldname)
{
	pfield feld;

	feld = malloc(sizeof(pfield));
	feld->fieldName = fieldname;
	feld->type = INTEGER;

	list_append(daoplan->fields, feld);
}

void daoplan_add_string(pDAOplan daoplan, char* fieldname, int len)
{
	pfield feld;

	feld = malloc(sizeof(pfield));
	feld->fieldName = fieldname;
	feld->type = STRING;
	feld->length = len;

	list_append(daoplan->fields, feld);
}

void daoplan_add_char(pDAOplan daoplan, char* fieldname, int len)
{
	pfield feld;

	feld = malloc(sizeof(pfield));
	feld->fieldName = fieldname;
	feld->type = CHARACTER;
	feld->length = len;

	list_append(daoplan->fields, feld);
}

void generate(pDAOplan daoplan)
{
	int i;
	pfield vfield;
	char* ddl = malloc(sizeof(char)*DDL_MAX_LENGTH);
	char numbuf[16];
	
	strcpy(ddl, "CREATE TABLE ");
	strcat(ddl, daoplan->structName);
    strcat(ddl, " (\n\tID INT NOT NULL\n");
    strcat(ddl, "\t, Create_Timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP\n");
    strcat(ddl, "\t, Created_By VARCHAR(255) NOT NULL\n");
    strcat(ddl, "\t, Update_Timestamp TIMESTAMP NULL\n");
    strcat(ddl, "\t, Updated_By VARCHAR(255) NULL\n");
	
	for(i=0; i<daoplan->fields->size; i++)
	{
		vfield = (pfield) list_get(daoplan->fields, i);
		switch(vfield->type) 
		{
			case INTEGER:
				strcat(ddl, "\t, ");
				strcat(ddl, vfield->fieldName);
				strcat(ddl, " INT NULL\n");
				break;
			case CHARACTER:
				strcat(ddl, "\t, ");
				strcat(ddl, vfield->fieldName);
				strcat(ddl, " CHAR(");
				snprintf (numbuf, (size_t)16, "%d", vfield->length);
				strcat(ddl, numbuf);
				strcat(ddl, ") NULL\n");
				break;
			case STRING:
				strcat(ddl, "\t, ");
				strcat(ddl, vfield->fieldName);
				strcat(ddl, " VARCHAR(");
				snprintf (numbuf, (size_t)16, "%d", vfield->length);
				strcat(ddl, numbuf);
				strcat(ddl, ") NULL\n");
				break;
		}
		refresh();
	}
	strcat(ddl, ");\n");
	printw("%s\n", ddl);
}
