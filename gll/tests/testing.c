#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gll.h"

typedef struct nametag_ {
	
	char name[50];
	unsigned int id;
	gl_thread_node_t gl_node; //the glue which connects the data and node
	
} nametag_t;

int main(int argc, char **argv) {
	
	/* Create the data being held by the list */
	
	nametag_t *n1 = calloc(1, sizeof(nametag_t));
	strncpy(n1->name, "Gabe", sizeof("Gabe"));
	n1->id = 1000;
	INIT_GL_THREAD((&n1->gl_node))
	
	nametag_t *n2 = calloc(1, sizeof(nametag_t));
	strncpy(n2->name, "Jeremy", sizeof("Jeremy"));
	n2->id = 1001;
	INIT_GL_THREAD((&n2->gl_node))
		
	nametag_t *n3 = calloc(1, sizeof(nametag_t));
	strncpy(n3->name, "Katrina", sizeof("Katrina"));
	n3->id = 1002;
	INIT_GL_THREAD((&n3->gl_node))
	
	/* Create the gl-thread */
	gl_thread_t *list = calloc(1, sizeof(gl_thread_t));
	gl_thread_init(list, offset_of(nametag_t, gl_node));
	
	gl_thread_add(list, &n1->gl_node);
	gl_thread_add(list, &n2->gl_node);
	gl_thread_add(list, &n3->gl_node);
	
	/* Iterate and print every new element */
	nametag_t *temp_ptr = NULL;
	ITERATE_GL_THREAD_BEGIN(list, nametag_t, temp_ptr) {
		printf("Nametag: %s\n", temp_ptr->name);
	} ITERATE_GL_THREAD_END;
	
	/* Remove the first element */
	gl_thread_rem(list, &n1->gl_node);
	
	/* Iterate after removing the first element */
	nametag_t *temp_ptr_2 = NULL;
	ITERATE_GL_THREAD_BEGIN(list, nametag_t, temp_ptr_2) {
		printf("Nametag: %s\n", temp_ptr_2->name);
	} ITERATE_GL_THREAD_END;
	
	return 0;
}