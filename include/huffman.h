/*
 * Header file : huffman.h
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Max value for extended ASCII 0-255 */
#define NB_MAX_CHAR 256


/*********************** STRUCTURES ***********************/

/* Array to store characters and their occurrence. */
typedef struct _data {
    unsigned char charact;  /* Initial character */
    unsigned occurr;        /* Character occurrence */
} data_t;

/* Huffman tree nodes. */
typedef struct _htree {
    unsigned char charact;  /* Initial character */
    unsigned occurr;        /* Character occurrence */
    unsigned code;          /* Huffman code */
    unsigned nbits;         /* Number of bits needed for Huffman code */
    struct _htree *left;    /* Left son in binary tree */
    struct _htree *right;   /* Right son in binary tree */
} htree_t, *ptrhtree;

/* Queue of tree nodes to build huffman tree. */
typedef struct _hqueue {
    ptrhtree tree;          /* Huffman tree node */
    struct _hqueue *next;   /* Next in queue */
} hqueue_t, *ptrhqueue;


/************************ FUNCTIONS ***********************/

/*************** File : func.c ***************/

/* Print usage and help information about project. */
void help();

/* Print version and authors of project. */
void version();

/* Check if __filename and __targetname are valid. 
   If __filename is valid, open file stream and return it. */
FILE *check_files(const char *__filename, const char *__targetname, const char *__ext1, const char *__ext2);

/* Copy in new data array only read characters and their occurrence. */
void array_copy(data_t array[], data_t cpy_array[], short size);

/* Sort data array by insertion in ascending order. */
void array_sort(data_t array[], short size);

/* Display the data array. */
void array_display(data_t array[], short size);

/* Push new node in priority queue.
   Return updated priority queue. */
ptrhqueue queue_push(ptrhqueue queue, ptrhtree tree);

/* Pop first node from priority queue.
   Return updated priority queue. */
ptrhqueue queue_pop(ptrhqueue queue);

/* Display the queue. */
void queue_display(ptrhqueue queue);

/* Free allocated memory of tree node in each queue node. 
   Free the entire queue. */
void queue_free(ptrhqueue queue);

/* Create tree node with a character and its occurence.
   Return the new tree node.*/
ptrhtree tree_create(unsigned char c, unsigned occ);

/* Display binary tree vertically. */
void tree_vdisplay(ptrhtree root, int level);

/* Free the entire binary tree. */
void tree_free(ptrhtree root);


/*************** File : encode.c ***************/

/* Store occurrence of characters from input_file in data array.
   Return number of different characters from input_file. */
short file_char_occurr(FILE *input_file, data_t array[]);

/* Fill empty queue with created tree nodes from data array. */
ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t array[], short size);

/* Create a parent tree with two sons.
   Smaller son will always be on left branch.
   Return parent tree. */
ptrhtree create_parent_tree(ptrhtree tree1, ptrhtree tree2);

/* Build Huffman tree using priority queue method.
   Return pointer to tree in the last node : root of
   huffman binary tree. */
ptrhtree build_huffman_tree(ptrhqueue queue);

/* Compress input file (.txt) into target binary file (.hff). */
void compression(const char *__filename, const char *__targetname);


/*************** File : decode.c ***************/

/* Decompress input binary file (.hff) into target file (.txt). */
void decompression(const char *__filename, const char *__targetname);

#endif