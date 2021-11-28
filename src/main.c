/*
 * Source file : main.c
 * CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#include "../include/huffman.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        if (argv[1] && strcmp(argv[1], "--help") == 0)
            help();
        else if (argv[1] && strcmp(argv[1], "--version") == 0)
            version();
        else {
            fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid arguments:\x1b[0m\n"
            "Run « \x1b[1m./bin/huffman --help\x1b[0m » for more information.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    if (argv[1] && argv[2] && argv[3]) {
        if (strcmp(argv[1], "-c") == 0)
            compression(argv[2], argv[3]);
        else if (strcmp(argv[1], "-d") == 0)
            decompression(argv[2], argv[3]);
        else {
            fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid arguments:\x1b[0m\n"
            "Run « \x1b[1m./bin/huffman --help\x1b[0m » for more information.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}