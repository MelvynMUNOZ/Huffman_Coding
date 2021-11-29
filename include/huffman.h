/**
 * Header file : huffman.h
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* Max value for extended ASCII 0-255 */
#define NB_MAX_CHAR 256


/*********************** STRUCTURES ***********************/

/* Dictionary to store data from characters. */
typedef struct _data {
    unsigned char charact;  /* Initial character */
    unsigned freq;        	 /* Character frequence */
	 unsigned hcode;          /* Huffman code */
    unsigned nbits;         /* Number of bits needed for Huffman code */
} data_t;

/* Huffman tree nodes. */
typedef struct _htree {
    unsigned char charact;  /* Initial character */
    unsigned freq;        	 /* Character frequence */
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

/* Check if __inputname and __outputname are valid. 
   If __inputname is valid, open stream and return it. */
FILE *check_files(const char *__inputname, const char *__outputname, const char *__ext1, const char *__ext2);

/* Copy in new data array only read characters and their frequence. */
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

/* Create tree node with a character and its frequence.
   Return the new tree node.*/
ptrhtree tree_create(unsigned char ch, unsigned freq);

/* Check if given tree is a leaf. */
int tree_is_leaf(ptrhtree tree);

/* Display binary tree vertically. */
void tree_vdisplay(ptrhtree root, int level);

/* Free the entire binary tree. */
void tree_free(ptrhtree root);


/*************** File : encode.c ***************/

/* Store frequence of characters from input_file in dico.
   Return number of different characters from input_file. */
short file_char_freq(FILE *input_file, data_t hdico[]);

/* Fill queue with created tree nodes from data array. */
ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t array[], short size);

/* Create a parent tree with two sons.
   Smaller son will always be on left branch.
   Return parent tree. */
ptrhtree create_parent_tree(ptrhtree tree1, ptrhtree tree2);

/* Build Huffman tree using priority queue method.
   Return pointer to tree in the last node : root of
   huffman binary tree. */
ptrhtree build_huffman_tree(ptrhqueue queue);

/* Get Huffman code and nbits of each characters.
   Store them in dico at character index. */
void get_huffman_code(ptrhtree root, data_t hdico[], unsigned code, unsigned nbits);

/* Write huffman dictionary at beginning of output file. */
void write_dico_in_output_file(const char *__outputname, data_t hdico[], short size);

/* Encode input file into output file.
   Write binary huffman code of each charaters from input file in output file. */
void encoding(const char *__inputname, const char *__outputname, data_t hdico[]);

/* Encode input file into output file using binary shifts and binary operators. */
void encoding(const char *__inputname, const char *__outputname, data_t hdico[]);

/* Compress input file (.txt) into output binary file (.hff). */
void compression(const char *__inputname, const char *__outputname);


/*************** File : decode.c ***************/

/* Decompress input binary file (.hff) into output file (.txt). */
void decompression(const char *__inputname, const char *__outputname);

#endif