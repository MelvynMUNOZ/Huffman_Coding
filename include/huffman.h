/*
 * Header file : huffman.h
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#ifndef huffman_h
#define huffman_h

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
} Data;

/* Huffman tree nodes. */
typedef struct _htree {
    unsigned char charact;  /* Initial character */
    unsigned occurr;        /* Character occurrence */
    struct _htree *left;    /* Left son in binary tree */
    struct _htree *right;   /* Right son in binary tree */
} Htree, *PtrHtree;

/* Queue of tree nodes to build huffman tree. */
typedef struct _queue {
    PtrHtree tree;          /* Huffman tree node */
    struct _queue *next;    /* Next in queue */
} Hqueue, *PtrHqueue;


/************************ FUNCTIONS ***********************/

/*************** File : func.c ***************/

/* Print usage and help information about project. */
void help();

/* Print version and authors of project. */
void version();

/* Check if _filename and _targetname are valid. 
   If _filename is valid, open it and return it. */
FILE *Check_Files(const char *_filename, const char *_targetname, const char *_ext1, const char *_ext2);

/* Copy in new data array only read characters and their occurrence. */
void Array_Copy(Data array[], Data cpy_array[], short size);

/* Sort data array by insertion in ascending order. */
void Array_Sort(Data array[], short size);

/* Display the data array.
   Return number of printed elements. */
int Array_Display(Data array[], short size);

/* Enqueue tree node in queue.
   Return queue with the new tree node. */
PtrHqueue Queue_Enqueue(PtrHqueue queue, PtrHtree tree);

/* Dequeue tree node from queue.
   Return the queue. */
PtrHqueue Queue_Dequeue(PtrHqueue queue);

/* Display the queue.
   Return number of printed elements. */
int Queue_Display(PtrHqueue queue);

/* Create tree node with a character and its occurence.
   Return the new tree node.*/
PtrHtree Tree_Create(unsigned char c, unsigned occ);

/* Display binary tree vertically. */
void Tree_VDisplay(PtrHtree root, int level);

/* Free the entire binary tree. */
void Tree_Free(PtrHtree root);


/*************** File : huff_encode.c ***************/

/* Store occurrence of characters from input_file in data array.
   Return number of different characters from input_file. */
short File_Char_Occurr(FILE *input_file, Data array[]);

/* Fill empty queue with created tree nodes from data array. */
PtrHqueue Fill_Queue_with_Tree(PtrHqueue queue, Data array[], short size);

/* Create a parent tree with two sons.
   Smaller son will always be on left branch.
   Return parent tree. */
PtrHtree Create_Parent_Tree(PtrHtree tree1, PtrHtree tree2);

/**/

/* Compress input file (.txt) into target binary file (.hff). */
void Compression(const char *_filename, const char *_targetname);


/*************** File : huff_decode.c ***************/

/* Decompress input binary file (.hff) into target file (.txt). */
void Decompression(const char *_filename, const char *_targetname);

#endif