/**
 * Source file : decode.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

void decompression(const char *__inputname, const char *__outputname)
{
    /* Check for valid file names and extensions. */
    FILE * input_file = NULL;
    input_file = check_files(__inputname, __outputname, ".hff", ".txt");
    printf("Decompressing %s ...\n", __inputname);
}