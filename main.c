#include <stdio.h>
#include <stdlib.h>
#include "include/oDAO.h"
#include "lib/LinkedList.h"

int main()
{
	pDAOplan plan;

	connect("");
	plan = registerDAO("DVD");
	printf("%s\n", plan->structName);

	return EXIT_SUCCESS;
}
