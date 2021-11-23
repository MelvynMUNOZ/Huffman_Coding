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

PtrHqueue Queue_Fill_with_Tree(PtrHqueue queue, Data array[], short size)
{
    /* Fill queue only if empty. */
    if (!queue) {
        PtrHtree node = NULL;
        for (short i = 0; i < size; i++) {
            /* Create tree node from data array and enqueue it in queue. */
            node = Tree_Create(array[i].charact, array[i].occurr);
            queue = Queue_Enqueue(queue, node);
        }
        return queue;
    }
    return NULL;
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
       Fill queue1 with trees created from data_array. */
    PtrHqueue queue1 = NULL, queue2 = NULL;
    queue1 = Queue_Fill_with_Tree(queue1, data_array, nb_char);
        Queue_Display(queue1);
    /* Build Huffman tree using 2 queues methode. */
    PtrHtree Huff_Tree = NULL;

    fclose(input_file);
}