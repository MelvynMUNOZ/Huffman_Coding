/*
 * Source file : func.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

void help()
{
    printf("\x1b[1mHUFFMAN CODING\x1b[0m\n\n"
    "\x1b[1mUSAGE\x1b[0m:\n\t./bin/huffman [-options] [input_file] [output_file]\n\n"
    "\x1b[1mOPTIONS:\x1b[0m\n"
    "\t\x1b[1m-c\x1b[0m\t\tCompress input file into binary output file.\n"
    "\t\x1b[1m-d\x1b[0m\t\tDecompress binary file.\n"
    "\t\x1b[1m--help\x1b[0m\t\tPrint usage and this help message and exit.\n"
    "\t\x1b[1m--version\x1b[0m\tPrint version and authors and exit.\n\n"
    "\x1b[1mDESCRIPTION:\x1b[0m\n"
    "\t[input_file] must be a (.txt) file when using [-c] option.\n"
    "\t[output_file] must be a (.hff) file when using [-c] option.\n\n"
    "\t[input_file] must be a (.hff) file when using [-d] option.\n"
    "\t[output_file] must be a (.txt) file when using [-d] option.\n\n"
    "\x1b[1mEXAMPLES:\x1b[0m\n"
    "\t./bin/huffman --help\n"
    "\t./bin/huffman -c message.txt encoded.hff\n"
    "\t./bin/huffman -d encoded.hff decoded.txt\n\n");
    exit(EXIT_SUCCESS);
}

void version()
{
    printf("huffman v1.0 - 2021 by Melvyn MUNOZ, Raphael CAUSSE"
    " - CY TECH PREING 2 MI\n\n");
    exit(EXIT_SUCCESS);
}

FILE *check_files(const char *__filename, const char *__targetname, const char *__exten1, const char *__exten2)
{
    FILE *input_file = NULL;
    /* Open __filename file to check if it exist. */
    input_file = fopen(__filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n"
        , __filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    short ext_check = strlen(__exten1)-1;
    /* Check if __targetname extension is valid. */
    if (__targetname[strlen(__targetname)-1] != __exten2[ext_check] 
    || __targetname[strlen(__targetname)-2] != __exten2[ext_check-1] 
    || __targetname[strlen(__targetname)-3] != __exten2[ext_check-2]) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid extension:\x1b[0m\n"
        "Please enter target file with \x1b[1m(%s)\x1b[0m extension.\n"
        "Run « \x1b[1m./bin/huffman --help\x1b[0m » information.\n\n", __exten2);
        exit(EXIT_FAILURE);
    }
    /* Check if __filename extension is valid. */
    if (__filename[strlen(__filename)-1] != __exten1[ext_check] 
    || __filename[strlen(__filename)-2] != __exten1[ext_check-1] 
    || __filename[strlen(__filename)-3] != __exten1[ext_check-2]) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid extension:\x1b[0m\n"
        "Please enter input file with \x1b[1m(%s)\x1b[0m extension.\n"
        "Run « \x1b[1m./bin/huffman --help\x1b[0m » for more information.\n\n", __exten1);
        exit(EXIT_FAILURE);
    }
    return input_file;
}

void array_copy(data_t array[], data_t cpy_array[], short size)
{
    for (short i = 0, j = 0; i < NB_MAX_CHAR && j < size; i++) {
        /* Copy only if there is an occurrence in array. */
        if (array[i].occurr == 0) {
            continue;
        }
        cpy_array[j].charact = array[i].charact;
        cpy_array[j].occurr = array[i].occurr;
        j++;
    }
}

void array_sort(data_t array[], short size)
{
    /* Insertion sort in ascending order. */
    short j;
    data_t tmp;
    for (short i = 1; i < size; i++) {
        tmp = array[i];
        j = i-1;
        while ((j >= 0) && (tmp.occurr < array[j].occurr)) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = tmp;
    }
}

void array_display(data_t array[], short size)
{
    if (!array) {
        printf("Empty array.\n");
        return;
    }
    printf("Nb different characters : %i\n",size);    
    for (short i = 0; i < size; i++) {  
        printf("%d\t%c / %u\n", i, array[i].charact, array[i].occurr); 
    }
    printf("\n");
}

ptrhqueue queue_push(ptrhqueue queue, ptrhtree tree)
{
    /* Memory allocation. */
    ptrhqueue new = calloc(1, sizeof(* new));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    /* Initialize new element. */
    *new = (hqueue_t) {.tree = tree, .next = NULL};
    if (!queue)
        return new;
    /* Push element in the priority queue. */
    ptrhqueue tmp = queue;
    while (tmp->next && tmp->next->tree->occurr < new->tree->occurr)
        tmp = tmp->next;
    new->next = tmp->next;
    tmp->next = new;
    return queue;
}

ptrhqueue queue_pop(ptrhqueue queue)
{
    if (!queue)
        return NULL;
    ptrhqueue tmp = queue->next;
    queue->next = NULL;
    free(queue);
    return tmp;
}

void queue_display(ptrhqueue queue)
{
    if (!queue) {
        printf("Empty queue.\n");
        return;
    }
    ptrhqueue p = queue;
    while (p) {
        printf("%c/%u | ", p->tree->charact, p->tree->occurr);   
        p = p->next;
    }
    printf("\n\n");
}

void queue_free(ptrhqueue queue)
{
    while (queue) {
        /* Free allocated memory for tree node then for queue node. */ 
        tree_free(queue->tree);
        queue = queue_pop(queue);
    }
}

ptrhtree tree_create(unsigned char c, unsigned occ)
{
    /* Memory allocation. */
    ptrhtree new = calloc(1, sizeof(*new));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    /* Initialize new element. */
    *new = (htree_t) {.charact = c, .occurr = occ, .left = NULL, .nbits = 0, .code = 0, .right = NULL};
    new->left = NULL; new->right = NULL;
    return new;
}

void tree_vdisplay(ptrhtree root, int level)
{
    if (root) {
        /* DFS preorder. */
        for (int i = 0; i < level; i++)
            printf((i == level-1) ? "└──" : "   ");
        printf("%c/%u\n", root->charact, root->occurr);
        tree_vdisplay(root->left, level+1);
        tree_vdisplay(root->right, level+1);
    }
}

void tree_free(ptrhtree root)
{
    if (root) {
        /* DFS postorder. */
        tree_free(root->left);
        tree_free(root->right);
        free(root);
        root = NULL;
    }
}