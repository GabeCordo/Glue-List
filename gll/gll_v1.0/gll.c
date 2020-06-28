#include <stdio.h>
#include <stdlib.h>
#include "gll.h"

/*
 * Function:  _add_gl_thread
 * -------------------------
 * a private function incharge of handling all the
 * pointer changes required when a new node is ad-
 * ded to the glue list
 *
 *  *curr: the node that will be after the insertion
 * 	*new: the node we are adding to the glue thread
 *
 */
void _add_gl_thread(gl_thread_node_t *curr, gl_thread_node_t *new) {
	
	//check to see if the pointer to the next node is NULL
	if (!curr->_node_next) {
		curr->_node_next = new;
		new->_node_prev = curr;
		return;
	}
	gl_thread_node_t *temp = curr->_node_next;
	curr->_node_next = new;
	new->_node_prev = curr;
	new->_node_next = temp;
	temp->_node_prev = new;
}

/*
 * Function:  gl_thread_add
 * ------------------------
 * add a new node into the glue thread that has been
 * initialized
 *
 *  *list: the glue threads list
 *  *gl_node: the new node that needs to be added
 *
 */
void gl_thread_add(gl_thread_t *list, gl_thread_node_t *gl_node) {
	
	gl_node->_node_next = NULL;
	gl_node->_node_prev = NULL;
	
	//check to see if the gl-thread has a node already
	if(!list->head) {
		list->head = gl_node;
		return;
	}
	gl_thread_node_t *gl_head = list->head;
	_add_gl_thread(gl_node, gl_head);
	list->head = gl_node;
}

/*
 * Function:  gl_thread_init
 * -------------------------
 * initialize the glue threads fields to the
 * appropriate default information
 *
 *  *list: a pointer to a gl_thread_t struct
 *  offset: the new node that needs to be added
 *
 */
void gl_thread_init(gl_thread_t *list, unsigned int offset) {
	
	list->head = NULL; //we will not have any nodes in the glue thread
	list->offset = offset;
	
}

/*
 * Function:  _rem_gl_thread
 * -------------------------
 * a private function incharge of handling all the
 * pointer changes required when a node is deleted
 *
 *  *node: the gl_thread_node within the list
 *
 */
void _rem_gl_thread(gl_thread_node_t *node) {
	
	//check to see if the prev-pointer is null
	if(!node->_node_prev) {
		if (node->_node_next) {
			node->_node_next->_node_prev = NULL;
			node->_node_next = 0;
			return;
		}
		return;
	}
	//check to see if the next pointer is null
	if(!node->_node_next) {
		if (node->_node_prev) {
			node->_node_prev->_node_next = NULL;
			node->_node_prev = NULL;
			return;
		}
		return;
	}
	//assume both pointers are not null and proceed with removing
	node->_node_prev->_node_next = node->_node_next;
	node->_node_next->_node_prev = node->_node_prev;
	node->_node_prev = 0;
	node->_node_next = 0;
}

/*
 * Function:  gl_thread_rem
 * ------------------------
 * the api for removing a data-node from a glue thread
 *
 *  *list: the glue thread where the node is embedded
 *	*gl_node: the node we are requesting the api to remove
 * 
 */
void gl_thread_rem(gl_thread_t *list, gl_thread_node_t *gl_node) {
	
	gl_thread_node_t *head = list->head; //create a temp variable to store the top of the list
	
	//if the node we are removing is the head of the glue thread, we just need to remove that
	if (head == gl_node)
		list->head = head->_node_next;
	//else we can proceed with running the private function to swap all required pointers
	_rem_gl_thread(gl_node);
}