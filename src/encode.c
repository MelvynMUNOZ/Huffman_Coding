/*
 * Source file : encode.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

short file_char_occurr(FILE *input_file, data_t array[])
{
    /* Read each character from input file and increment in array their occurrence.
       Array index are their ASCII value. (extended ASCII 0-255) */
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

ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t array[], short size)
{
    /* Fill queue only if empty. */
    if (!queue) {
        ptrhtree node = NULL;
        for (short i = 0; i < size; i++) {
            /* Create tree node from data array. Enqueue in queue. */
            node = tree_create(array[i].charact, array[i].occurr);
            queue = queue_push(queue, node);
        }
        return queue;
    }
    return NULL;
}

ptrhtree create_parent_tree(ptrhtree tree1, ptrhtree tree2)
{
    ptrhtree parent = tree_create('$', tree1->occurr + tree2->occurr);
    if (tree1->occurr <= tree2->occurr) {
        parent->left = tree1;
        parent->right = tree2;
    } else {
        parent->left = tree2;
        parent->right = tree1;
    }
    return parent;
}

ptrhtree build_huffman_tree(ptrhqueue priority_queue)
{
    ptrhtree node1 = NULL, node2 = NULL;
    /* Create parent tree node with first two node of priority queue.
       Pop priority queue twice and push parent tree node in it. 
       Repeat until it remains only one node in priority queue. */
    while (priority_queue && priority_queue->next) {
        node1 = priority_queue->tree;
        node2 = priority_queue->next->tree;
        priority_queue = queue_pop(priority_queue);
        priority_queue = queue_pop(priority_queue);
        priority_queue = queue_push(priority_queue, create_parent_tree(node1, node2));
    }
    /* Last node of priority queue contains the root of huffman tree. */
    ptrhtree root = priority_queue->tree;
    /* Free last node of priority queue to prevent memory leaks. */
    priority_queue = queue_pop(priority_queue);
    return root;
}

void compression(const char *__filename, const char *__targetname)
{
    /* Check for valid file name and extensions. */
    FILE *input_file = NULL;
    input_file = check_files(__filename, __targetname, ".txt", ".hff");
    /* Store occurrence of characters in tmp_array. */
    data_t tmp_array[NB_MAX_CHAR] = {{0},{0}};
    short nb_char = file_char_occurr(input_file, tmp_array);
    /* Copy tmp_array in data_array only read characters.
       Then sort data_array in ascending order. */
    data_t data_array[nb_char];
    array_copy(tmp_array, data_array, nb_char);
    array_sort(data_array, nb_char);
        array_display(data_array, nb_char);
    /* Init a fill priority queue with tree nodes created from data_array. */
    ptrhqueue priority_queue = NULL;
    priority_queue = fill_queue_with_tree(priority_queue, data_array, nb_char);
        queue_display(priority_queue);
    /* Build Huffman tree using priority queue method. */
    ptrhtree huffman_tree = NULL;
    huffman_tree = build_huffman_tree(priority_queue);
        tree_vdisplay(huffman_tree, 0);

    tree_free(huffman_tree);
    fclose(input_file);
    // fclose(bin_file);
}