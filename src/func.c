/*
 * Source file : func.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

void help()
{
    system("clear");
    printf("\x1b[1mHUFFMAN CODING\x1b[0m\n\n"
    "\x1b[1mUSAGE\x1b[0m:\n\t./bin/huffman [-options] [input_filename] [output_filename]\n\n"
    "\x1b[1mOPTIONS:\x1b[0m\n"
    "\t\x1b[1m-c\x1b[0m\t\tCompress input file into binary output file.\n"
    "\t\x1b[1m-d\x1b[0m\t\tDecompress binary file.\n"
    "\t\x1b[1m--help\x1b[0m\t\tPrint usage and this help message and exit.\n"
    "\t\x1b[1m--version\x1b[0m\tPrint version and authors and exit.\n\n"
    "\x1b[1mDESCRIPTION:\x1b[0m\n"
    "\t[input_filename] must be a (.txt) file when using [-c] option.\n"
    "\t[output_filename] must be a (.hff) file when using [-c] option.\n\n"
    "\t[input_filename] must be a (.hff) file when using [-d] option.\n"
    "\t[output_filename] must be a (.txt) file when using [-d] option.\n\n"
    "\x1b[1mEXAMPLES:\x1b[0m\n"
    "\t./bin/huffman --help\n"
    "\t./bin/huffman -c message.txt encoded.hff\n"
    "\t./bin/huffman -d encoded.hff decoded.txt\n\n");
    exit(EXIT_SUCCESS);
}

void version()
{
    printf("huffman v1.0.0 - 2021 by Melvyn MUNOZ, Raphael CAUSSE"
    " - CY TECH PREING 2 MI\n\n");
    exit(EXIT_SUCCESS);
}

FILE *Check_Files(const char *_filename, const char *_targetname, const char *_exten1, const char *_exten2)
{
    FILE *input_file = NULL;
    /* Open _filename file to check if it exist. */
    input_file = fopen(_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n"
        , _filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    short ext_check = strlen(_exten1)-1;
    /* Check if _targetname extension is valid. */
    if (_targetname[strlen(_targetname)-1] != _exten2[ext_check] 
    || _targetname[strlen(_targetname)-2] != _exten2[ext_check-1] 
    || _targetname[strlen(_targetname)-3] != _exten2[ext_check-2]) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid extension:\x1b[0m\n"
        "Please enter target file with \x1b[1m(%s)\x1b[0m extension.\n\n"
        "Run « \x1b[1m./bin/huffman --help\x1b[0m » information.\n\n", _exten2);
        exit(EXIT_FAILURE);
    }
    /* Check if _filename extension is valid. */
    if (_filename[strlen(_filename)-1] != _exten1[ext_check] 
    || _filename[strlen(_filename)-2] != _exten1[ext_check-1] 
    || _filename[strlen(_filename)-3] != _exten1[ext_check-2]) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid extension:\x1b[0m\n"
        "Please enter input file with \x1b[1m(%s)\x1b[0m extension.\n\n"
        "Run « \x1b[1m./bin/huffman --help\x1b[0m » for more information.\n\n", _exten1);
        exit(EXIT_FAILURE);
    }
    return input_file;
}

void Array_Copy(Data array[], Data cpy_array[], short size)
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

void Array_Sort(Data array[], short size)
{
    /* Insertion sort in ascending order. */
    short j;
    Data tmp;
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

int Array_Display(Data array[], short size)
{
    if (!array) {
        printf("Empty array.\n");
        return 0;
    }
    int check = 0;
    printf("Nb read char : %i\n",size);    
    for (short i = 0; i < size; i++) {  
        printf("%d\t%c / %u\n", i, array[i].charact, array[i].occurr);
        check++; 
    }
    printf("\n\n");
    return check;
}

PtrHqueue Queue_Enqueue(PtrHqueue queue, PtrHtree tree)
{
    /* Memory allocation. */
    PtrHqueue new = calloc(1, sizeof(Hqueue));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    new->next = NULL;
    new->tree = tree;
    if (!queue)
        return new;
    /* If queue is not empty, add at the end of queue. */
    else {
        PtrHqueue tmp = queue;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
        return queue;
    }
}

PtrHqueue Queue_Dequeue(PtrHqueue queue)
{
    if (!queue)
        return NULL;
    PtrHqueue tmp = queue->next;
    queue->next = NULL;
    free(queue);
    return tmp;
}

int Queue_Display(PtrHqueue queue)
{
    if (!queue) {
        printf("Empty queue.\n");
        return 0;
    }
    int check = 0;
    PtrHqueue p = queue;
    while (p) {
        printf("%c/%u | ", p->tree->charact, p->tree->occurr);   
        p = p->next;
        check++;
    }
    printf("\n\n");
    return check;
}

PtrHtree Tree_Create(unsigned char c, unsigned occ)
{
    /* Memory allocation. */
    PtrHtree new = calloc(1, sizeof(Htree));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    new->charact = c;
    new->occurr = occ;
    new->nbits = 0;
    new->left = NULL; new->right = NULL;
    return new;
}

void Tree_VDisplay(PtrHtree root, int level)
{
    if (root) {
        for (int i = 0; i < level; i++)
            printf((i == level-1) ? "└──" : "   ");
        printf("%c/%u\n", root->charact, root->occurr);
        Tree_VDisplay(root->left, level+1);
        Tree_VDisplay(root->right, level+1);
    }
}

void Tree_Free(PtrHtree root)
{
    if (root) {
        Tree_Free(root->left);
        Tree_Free(root->right);
        free(root);
        root = NULL;
    }
}