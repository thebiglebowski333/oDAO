#include "../lib/LinkedList.h"

#ifndef _ODAO_H_
#define _ODAO_H_

#define CONNECTION_ESTABLISHED 0

enum datatype
{
	INTEGER, 
	CHARACTER,
	STRING
};

typedef enum datatype datatype_t;

struct field
{
	char* fieldName;
	datatype_t type;
	int length;
	int precision;
};

typedef struct field field_t;

typedef field_t* pfield;

struct DAOplan
{
	char* structName;
	plinked_list fields;
	char* host;
};

typedef struct DAOplan DAOplan_t;

typedef DAOplan_t *pDAOplan;

struct DB_values {
	char* host;
	char* user;
	char* pwd;
	char* dbname;
};

typedef struct DB_values DB_values_t;

typedef DB_values_t* pDB_values;

int executeDDL(pDB_values values, char** stmts, int stmtcount);

DAOplan_t* registerDAO(char* structName);

/**
 * Generates files <daoname>.c, <daoname>.h, <daoname>DAO.c, <daoname>DAO.h
 * and tables in defined database
 */
void generate(pDAOplan daoplan);

void daoplan_add_int(pDAOplan daoplan, char* fieldname);

void daoplan_add_string(pDAOplan daoplan, char* fieldname, int len);

void daoplan_add_char(pDAOplan daoplan, char* fieldname, int len);

/* ich hab gehört ich soll mal was comitten */

#endif
