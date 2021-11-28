/*
 * Source file : decode.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

void decompression(const char *__filename, const char *__targetname)
{
    /* Check for valid file name and extensions. */
    FILE * input_file = NULL;
    input_file = check_files(__filename, __targetname, ".hff", ".txt");
}