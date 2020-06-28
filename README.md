# Glue List ~ Alternative to Doubly Linked Lists

Glue lists are commonly seen within the linux architecture, this implementation is merely an attempt to rebuild
the wheel with the hope of gaining a deeper-understanding of its advantages.

* Commonly referred to as "Glue Threads", they are dynamic allocated data-structure similar to doubly linked lists. 
* Glue threads do not use pointers within the node to access arbitrary data.
* Takes advantage of memory address offsets to access data associated with a node.

## Advantages

* When linked-data must be reference from multiple data structures.
* Avoids the need to independently iterate over the data-structures referencing the node.
	* The node containing next/previous pointers are attached to the data unlike linked lists.
	* This allows data-objects to be freed without the need to remove multiple pointer references.

## Implementation

'~:gll/tests/test.c' is an example of a glue thread implementation for C structures.