#ifndef HEADER_FILE
#define HEADER_FILE

	/* typedef deffinitions */
	
	typedef struct gl_thread_node {
		
		struct gl_thread_node *_node_prev;
		struct gl_thread_node *_node_next;
		
	} gl_thread_node_t;
	
	typedef struct gl_thread_head {
		
		gl_thread_node_t *head;
		unsigned int offset;
		
	} gl_thread_t;
	
	/* macro deffinitions */
	
	#define ITERATE_GL_THREAD_BEGIN(list_ptr, struct_type, struct_ptr)		\
	{																		\
		gl_thread_node_t *node = NULL, *next = NULL;						\
		for(node = list_ptr->head; node; node = next) {						\
			next = node->_node_next;										\
			struct_ptr = (struct_type *)((char *)node - list_ptr->offset);
	
	#define ITERATE_GL_THREAD_END }}
	
	#define INIT_GL_THREAD(gl_thread_node)	\
		gl_thread_node->_node_prev = NULL;	\
		gl_thread_node->_node_next = NULL;
	
	#define offset_of(struct_name, field_name)	\
		((unsigned int)&((struct_name *)0)->field_name)
	
	/* function deffinitions */
	
	void gl_thread_add(gl_thread_t *list, gl_thread_node_t *gl_node);
	void gl_thread_init(gl_thread_t *list, unsigned int offset);
	void gl_thread_rem(gl_thread_t *list, gl_thread_node_t *gl_node);
	
#endif