/*
 * Source file : encode.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

short file_char_freq(FILE *input_file, data_t dico[])
{
    /* Read each character from input file and increment in array their frequence.
       Array index are their ASCII value. (extended ASCII 0-255) */
    int c = 0;
    while ((c = fgetc(input_file)) != EOF) {
        dico[c].charact = c;
        dico[c].freq++;
    }
    /* Return number of different characters. */
    short nb_char = 0;
    for (short i = 0; i < NB_MAX_CHAR; i++) {
        if (dico[i].freq == 0) {
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
            node = tree_create(array[i].charact, array[i].freq);
            queue = queue_push(queue, node);
        }
        return queue;
    }
    return NULL;
}

ptrhtree create_parent_tree(ptrhtree tree1, ptrhtree tree2)
{
    ptrhtree parent = tree_create('$', tree1->freq + tree2->freq);
    if (tree1->freq <= tree2->freq) {
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

void get_huffman_code(ptrhtree root, data_t dico[], unsigned bin_code, unsigned nbits)
{
    /* DFS preorder : go to left : 0 and go to right : 1. */ 
    if (tree_is_leaf(root)) {
        /* Store in dico at character index its code and nbits for its code. */
        dico[root->charact].code = bin_code;
        dico[root->charact].nbits = nbits;
        return;
    }
    if (root->left) {
        /* Shift code 1 bit to the left, concat bit 0. Increment the nbits. */
        get_huffman_code(root->left, dico, (bin_code<<1), nbits+1);
    }
    if (root->right) {
        /* Shift code 1 bit to the left, concat bit 1. Increment the nbits. */
        get_huffman_code(root->right, dico, (bin_code<<1)+1, nbits+1);
    }
}

/* dico_write */
/* encoding */

void compression(const char *__filename, const char *__targetname)
{
    /* Check for valid file name and extensions. */
    FILE *input_file = NULL;
    input_file = check_files(__filename, __targetname, ".txt", ".hff");
    printf("Compressing %s ...\n", __filename);
    /* Store frequence of characters in dico. */
    data_t dico[NB_MAX_CHAR] = {{0},{0},{0},{0}};
    short nb_char = file_char_freq(input_file, dico);
    /* Copy tmp_array in data_array only read characters.
       Then sort data_array in ascending order. */
    data_t data_array[nb_char];
    array_copy(dico, data_array, nb_char);
    array_sort(data_array, nb_char);
        /* Check. 
        array_display(data_array, nb_char); */
    /* Init and fill priority queue with tree nodes created from data_array. */
    ptrhqueue priority_queue = NULL;
    priority_queue = fill_queue_with_tree(priority_queue, data_array, nb_char);
        /* Check. 
        queue_display(priority_queue); */
    /* Build Huffman tree using priority queue method. */
    ptrhtree huffman_tree = NULL;
    huffman_tree = build_huffman_tree(priority_queue);
        /* Check.
        tree_vdisplay(huffman_tree, 0); */
    get_huffman_code(huffman_tree, dico, 0, 0);
        /* Check.
        array_display(dico, NB_MAX_CHAR); */

    tree_free(huffman_tree);
    fclose(input_file);
    // fclose(bin_file);
}