#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
	
struct node
{
	struct node* next;
	struct node* previous;
	void* content;
};

typedef struct node node_t;

typedef node_t* pnode;

struct linked_list
{
	pnode head;
	pnode last;
	pnode runner;
	int runnerpos;
	int size;
};

typedef struct linked_list linked_list_t;

typedef linked_list_t* plinked_list;

void list_append(plinked_list list, void* value);

void list_insert(plinked_list list, int position, void* value);

void list_remove(plinked_list list, int position);

void* list_get(plinked_list list, int position);

void list_add_all(plinked_list list, void** elems, int count);

plinked_list init_list();

#endif
