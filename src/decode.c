/*
 * Source file : decode.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

void Decompression(const char *_filename, const char *_targetname)
{
    /* Check for valid file name and extensions. */
    FILE * input_file = NULL;
    input_file = Check_Files(_filename, _targetname, ".hff", ".txt");
}