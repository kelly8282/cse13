#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define OPTIONS "hvi:o:"
int main(int argc, char **argv) {
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int opt = 0;
    bool verbose = false;
    bool help = false;

    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        default: help = true; break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "error message");
                return 1;
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                fprintf(stderr, "error message");
                return 1;
            }
            break;
        }
    }
    if (help == true) {
        printf("SYNOPSIS\n");
        printf("  A Huffman encoder.\n");
        printf("  Compresses a file using the Huffman coding algorithm.\n");

        printf("USAGE\n");
        printf("  ./encode [-h] [-i infile] [-o outfile]");

        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -v             Print compression statistics.\n");
        printf("  -i infile      Input file to compress.\n");
        printf("  -o outfile     Output of compressed data.\n");
        return 0;
    }

    uint64_t histogram[ALPHABET] = { 0 };
    uint32_t symbols = 0;
    uint8_t buffe[BLOCK] = { 0 };
    histogram[0]++;
    histogram[255]++;
    symbols += 2;
    uint64_t b_read = 0;
    while ((b_read = read_bytes(infile, buffe, BLOCK)) > 0) {
        for (uint32_t i = 0; i < b_read; i++) {
            if (histogram[buffe[i]] == 0) {
                symbols = symbols + 1;
            }
            histogram[buffe[i]]++;
        }
    }
    Node *root = build_tree(histogram);
    Code table[ALPHABET] = { 0 };
    build_codes(root, table);

    struct stat buff;
    fstat(infile, &buff);
    fchmod(outfile, buff.st_mode);
    Header header = { 0, 0, 0, 0 };
    header.magic = MAGIC;
    header.permissions = buff.st_mode;
    header.tree_size = (3 * symbols) - 1;
    header.file_size = buff.st_size;
    write_bytes(outfile, (uint8_t *) &header, sizeof(header));

    dump_tree(outfile, root);
    lseek(infile, 0, SEEK_SET);

    while ((b_read = read_bytes(infile, buffe, BLOCK)) > 0) {
        for (uint64_t i = 0; i < b_read; i++) {
            write_code(outfile, &table[buffe[i]]);
        }
    }
    flush_codes(outfile);
    if (verbose == true) {
        printf("stats"); //print stats need to do
    }
    delete_tree(&root);
    close(infile);
    close(outfile);
}
