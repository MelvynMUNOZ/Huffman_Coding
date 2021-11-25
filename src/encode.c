/*
 * Source file : encode.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

short File_Char_Occurr(FILE *input_file, Data array[])
{
    /* Read each character from input file and increment in array their occurrence.
       Array index are their ASCII value. (extended ASCII) */
    int c = 0;
    while ((c = fgetc(input_file)) != EOF) {
        array[c].charact = c;
        array[c].occurr++;
    }
    /* Count number of different characters. */
    short nb_char = 0;
    for (short i = 0; i < NB_MAX_CHAR; i++) {
        if (array[i].occurr == 0) {
            continue;
        }
        nb_char++;
    }
    return nb_char;
}

PtrHqueue Fill_Queue_with_Tree(PtrHqueue queue, Data array[], short size)
{
    /* Fill queue only if empty. */
    if (!queue) {
        PtrHtree node = NULL;
        for (short i = 0; i < size; i++) {
            /* Create tree node from data array and enqueue in queue. */
            node = Tree_Create(array[i].charact, array[i].occurr);
            queue = Queue_Enqueue(queue, node);
        }
        return queue;
    }
    return NULL;
}

PtrHtree Create_Parent_Tree(PtrHtree tree1, PtrHtree tree2)
{
    PtrHtree parent = Tree_Create('$', tree1->occurr + tree2->occurr);
    if (tree1->occurr <= tree2->occurr) {
        parent->left = tree1;
        parent->right = tree2;
    } else {
        parent->left = tree2;
        parent->right = tree1;
    }
    return parent;
}

PtrHtree Build_Huffman_Tree(PtrHqueue queue1, PtrHqueue queue2, short size)
{
    /* Build huffman tree takes size-1 steps, with size the size of queue1 at first. */
    for (short i = 0; i < size -1; i++) {
        /* If queue2 is empty, create parent node with two first nodes of queue1.
           Dequeue twice queue2 and enqueue the parent node in queue2. */
        if (!queue2){

        }
        /* If queue1 is empty, create parent node with two first nodes of queue2.
           Dequeue twice queue2 and enqueue the parent node in queue2. */
        if (!queue1) {

        }
        /* If first node of queue1 is equal or smaller than first node of queue2. */
        if (queue1->tree->occurr <= queue2->tree->occurr) {
            /* Create parent node with two first nodes of queue1.
               Dequeue queue1 twice. Enqueue parent node in queue2. */
            if (queue1->next->tree->occurr < queue2->tree->occurr) {

            }
            /* Else, create parent node with first node of queue1 and first node of queue2.
               Dequeue queue1 and queue2. Enqueue parent node in queue2. */
            else {

            }
        }
        /* If first node of queue1 is greater than first node of queue2. */
        else {
            /* Create parent node with two first nodes of queue2.
               Dequeue queue2 twice. Enqueue parent node in queue2. */
            if (queue2->next->tree->occurr < queue1->tree->occurr) {

            }
            /* Else, create parent node with first node of queue1 and first node of queue2.
               Dequeue queue1 and queue2. Enqueue parent node in queue2. */
            else {

            }
        }
    }
    /* Last node of queue2 contains the root of huffman tree. */
    return queue2->tree;
}

void Compression(const char *_filename, const char *_targetname)
{
    /* Check for valid file name and extensions. */
    FILE *input_file = NULL;
    input_file = Check_Files(_filename, _targetname, ".txt", ".hff");
    /* Store occurrence of characters in tmp_array. */
    Data tmp_array[NB_MAX_CHAR] = {{0},{0}};
    short nb_char = File_Char_Occurr(input_file, tmp_array);
    /* Copy tmp_array in data_array only read characters.
       Then sort data_array in ascending order. */
    Data data_array[nb_char];
    Array_Copy(tmp_array, data_array, nb_char);
    Array_Sort(data_array, nb_char);
    /* Init 2 queues.
       Fill queue1 with trees created from data_array. 
       Queue2 is empty and will be used to enqueue each parent tree created.*/
    PtrHqueue queue1 = NULL, queue2 = NULL;
    queue1 = Fill_Queue_with_Tree(queue1, data_array, nb_char);
    /* Build Huffman tree using two queues method. */
    PtrHtree Huff_Tree = NULL;

    fclose(input_file);
}