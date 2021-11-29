/**
 * Source file : encode.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

short file_char_freq(FILE *input_file, data_t hdico[])
{
    /* Read each character from input file and increment in array their frequence.
       Array index are their ASCII value. (extended ASCII 0-255) */
    int c = 0;
    while ((c = fgetc(input_file)) != EOF) {
        hdico[c].charact = c;
        hdico[c].freq++;
    }
    /* Return number of different characters. */
    short nb_char = 0;
    for (short i = 0; i < NB_MAX_CHAR; i++) {
        if (hdico[i].freq == 0) {
            continue;
        }
        nb_char++;
    }
    fclose(input_file);
    return nb_char;
}

ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t array[], short size)
{
    /* Fill queue only if empty at first. */
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
    /* Create parent node with two sons. */
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

void get_huffman_code(ptrhtree root, data_t hdico[], unsigned bin_code, unsigned nbits)
{
    /* DFS preorder : go to left : 0 and go to right : 1. */ 
    if (tree_is_leaf(root)) {
        /* Store in dictionary at character index its code and nbits for its code. */
        hdico[root->charact].hcode = bin_code;
        hdico[root->charact].nbits = nbits;
        return;
    }
    if (root->left) {
        /* Shift code 1 bit to the left, concat bit 0. Increment the nbits. */
        get_huffman_code(root->left, hdico, (bin_code<<1), nbits+1);
    }
    if (root->right) {
        /* Shift code 1 bit to the left, concat bit 1. Increment the nbits. */
        get_huffman_code(root->right, hdico, (bin_code<<1)+1, nbits+1);
    }
}

void write_dico_in_output_file(const char *__outputname, data_t hdico[], short size)
{
    FILE *output_file = NULL;
    /* Open stream to __outputname, write mode. */
    output_file = fopen(__outputname, "w");
    if (output_file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n"
        , __outputname, strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* Write characters and their frequence at beginning of output_file. */
    fprintf(output_file, "%i|", size);
    for (short i = 0; i < NB_MAX_CHAR; i++){
        if (hdico[i].freq == 0) continue;
        fprintf(output_file, "%u;%c|", hdico[i].freq, hdico[i].charact);            
    }
    fclose(output_file);
}

void encoding(const char *__inputname, const char *__outputname, data_t hdico[])
{
    float nbits_input = 0, nbits_output = 0; 
    FILE *input_file = NULL, *output_file = NULL;
    /* Open stream to __inputname, read mode. */
    input_file = fopen(__inputname, "r");
    if (input_file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n"
        , __inputname, strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* Open stream to __outputname, binary write mode, set at end of file. */
    output_file = fopen(__outputname, "ab");
    if (output_file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n"
        , __outputname, strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* Read each character from input_file and write its huffman code in output_file. */
    int read_char = 0;
    unsigned char cbin = 0;
    unsigned buffer = 0, buffer_size = 0; 
    while ((read_char = fgetc(input_file)) != EOF) {
        /* Shift buffer to left by nbits needed for the read character. Add nbits to buffer_size. */
        buffer = (buffer << hdico[read_char].nbits);
        buffer_size += hdico[read_char].nbits;
        /* Concat bits of huffman code of the read character, using a binary mask (OR operator). */
        buffer = (buffer | hdico[read_char].hcode);
        /* When buffer contains at least 8 bits, write those 8 bits, as a char, in output_file. */
        while (buffer_size >= 8) {
            buffer_size -= 8;
            /* Shift buffer to right by buffer_size - 8, to get the first 8 bits in a char to
               write it. */
            cbin = (buffer >> buffer_size);

            /* try with fwrite */
            fputc(cbin, output_file); 

            /* Update count of nbits written in output_file. */
            nbits_output += 8;
        }
        /* Update count of nbits read in input_file. */
        nbits_input += 8;
    }
    /* If buffer ends up not full (under 8), concat bits 0 to fulfill it, then write it. */
    if (buffer_size && buffer_size < 8) {
        cbin = (buffer << (8-buffer_size));
        
        /* try with fwrite */
        fputc(cbin, output_file);
        
        /* Update count of nbits written in output_file. */
        nbits_output += 8;
    }
    /* Compression efficiency. */
    printf("%.f kb compressed to %.f kb [%.1f %%].\n"
    , nbits_input/1000, nbits_output/1000, 100-((nbits_output/nbits_input)*100));
    fclose(output_file);
    fclose(input_file);
}

void compression(const char *__inputname, const char *__outputname)
{
    clock_t start, end;
    double time_taken;
    /* Check for valid file names and extensions. */
    FILE *input_file = NULL;
    input_file = check_files(__inputname, __outputname, ".txt", ".hff");
    printf("Compressing %s ...\n", __inputname);
    start = clock();
    /* Store frequence of characters in dictionary. */
    data_t hdico[NB_MAX_CHAR] = {{0},{0},{0},{0}};
    short nb_char = file_char_freq(input_file, hdico);
    /* Copy tmp_array in data_array only read characters.
       Then sort data_array in ascending order. */
    data_t data_array[nb_char];
    array_copy(hdico, data_array, nb_char);
    array_sort(data_array, nb_char);
        /* Check. array_display(data_array, nb_char); */
    /* Init and fill priority queue with tree nodes created from data_array. */
    ptrhqueue priority_queue = NULL;
    priority_queue = fill_queue_with_tree(priority_queue, data_array, nb_char);
        /* Check. queue_display(priority_queue); */
    /* Build Huffman tree using priority queue method. */
    ptrhtree huffman_tree = NULL;
    huffman_tree = build_huffman_tree(priority_queue);
        /* Check. tree_vdisplay(huffman_tree, 0); */
    get_huffman_code(huffman_tree, hdico, 0, 0);
        /* Check. array_display(hdico, NB_MAX_CHAR); */
    tree_free(huffman_tree);
    /* Write huffman dictionary at beginning of output file. */
    write_dico_in_output_file(__outputname, hdico, nb_char);
    /* Encode input file into output file. */
    encoding(__inputname, __outputname, hdico);
    /* Time in seconds. */
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Done in %.3f s.\n\n", time_taken);
}