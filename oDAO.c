#include "include/oDAO.h"
#include "lib/LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>

void connect(char* dbstring)
{
	SQLHENV env;
	SQLHDBC dbc;
	SQLHSTMT stmt;
	SQLRETURN retval;
	long res;
	char* output;
	SQLSMALLINT outlen;
	SQLSMALLINT cols;
	SQLUSMALLINT i;
	SQLLEN indicator;
	int row = 0;

	char *connectionString =
			"DRIVER={MySQL ODBC 3.51 Driver};\
		                   SERVER=localhost;\
		                   DATABASE=Pension;\
		                   USER=root;\
		                   PASSWORD=Schaatz1409;\
		                   OPTION=3;";

	output = malloc(255 * sizeof(char));

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);

	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);

	retval = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
	if (retval != SQL_SUCCESS)
	{
		printf("Error...\n");
	}
	else
	{
		printf("%d\n", retval);
		res = SQLDriverConnect(dbc, 0, (SQLCHAR*) connectionString,
				strlen(connectionString), output, 255, &outlen,
				SQL_DRIVER_COMPLETE);
		if (retval != SQL_SUCCESS)
		{
			printf("Error while connecting...\n");
		}
		else
		{
			printf("connected\n");
			retval = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
			printf("%d\n", retval);
			retval = SQLTables(stmt, NULL, 0, NULL, 0, NULL, 0, "TABLE", SQL_NTS);
			printf("%d\n", retval);
			SQLNumResultCols(stmt, &cols);

			printf("while begin\n");
			while (SQL_SUCCEEDED(retval = SQLFetch(stmt)))
			{
				printf("Row %d\n", row++);
				for (i = 0; i <= cols; i++)
				{
					retval = SQLGetData(stmt, i, SQL_C_CHAR, output, 255,
							&indicator);
					if (SQL_SUCCEEDED(retval))
					{
						if (&indicator == NULL )
							strcpy(output, "NULL");
						printf("Column %u: %s", i, output);
					}
				}
			}

			printf("while end\n", retval);

			SQLDisconnect(dbc);
			SQLFreeHandle(SQL_HANDLE_STMT, &stmt);
			SQLFreeHandle(SQL_HANDLE_DBC, &dbc);
			SQLFreeHandle(SQL_HANDLE_ENV, &env);
		}
	}
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
	pfield field;

	field = malloc(sizeof(pfield));
	field->fieldName = fieldname;
	field->type = INTEGER;

	list_append(daoplan->fields, field);
}

void daoplan_add_string(pDAOplan daoplan, char* fieldname, int len)
{

}

void generate(pDAOplan daoplan)
{

}
