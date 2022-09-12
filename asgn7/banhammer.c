#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "messages.h"
#include "bv.h"
#include "bf.h"
#include "node.h"
#include "speck.h"
#include "parser.h"
#include "ht.h"
#include "bst.h"
#include <regex.h>
#include <math.h>
#define OPTIONS "ht:f:s"
#define WORD    "[0-9a-zA-Z_]+([-'][0-9a-zA-Z_]+)*"

int main(int argc, char **argv) {
    int opt = 0;
    regex_t re;
    uint32_t hsize = pow(2, 16);
    uint32_t bsize = pow(2, 20);
    bool help = false;
    bool stats = false;
    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        default: help = true; break;
        case 'h': help = true; break;
        case 't': hsize = atoi(optarg); break;
        case 'f': bsize = atoi(optarg); break;
        case 's': stats = true; break;
        }
    }
    if (help == true) { //helper function
        printf("SYNOPSIS\n");
        printf("  A word filtering program for the GPRSC.\n");
        printf("  Filters out and reports bad words parsed from stdin.\n\n");
        printf("USAGE\n");
        printf("  ../../resources/asgn7/banhammer [-hs] [-t size] [-f size]\n\n)");
        printf("OPTIONS\n");
        printf("  -h           Program usage and help.\n");
        printf("  -s           Print program statistics.\n");
        printf("  -t size      Specify hash table size (default: 2^16).\n");
        printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
        return 0;
    }
    //create my bloomfilter and hashtable
    BloomFilter *bf = bf_create(bsize);
    HashTable *ht = ht_create(hsize);

    if (regcomp(&re, WORD, REG_EXTENDED)) { //make sure regex works
        fprintf(stderr, "Failed to compile regex.\n");
        return 0;
    }

    FILE *bs = fopen("badspeak.txt", "r"); //open badspeak
    if (bs == NULL) { //make sure badspeak.txt is not null
        fprintf(stderr, "Error opening badpseak.txt.\n");
        fclose(bs);
        return 0;
    }

    char line[4096]; //create a temporary variable
    while (fscanf(bs, "%[^\n] ", line) != EOF) { //read line by line until end of file
        bf_insert(bf, line); //insert into bloom filter
        ht_insert(ht, line, NULL); //insert into hash table filter
    }
    FILE *ns = fopen("newspeak.txt", "r"); //open newspeak
    if (ns == NULL) { //make sure newspeak.txt is not null
        fprintf(stderr, "Error opening newspeak.txt.\n");
        fclose(ns);
        fclose(bs);
        return 0;
    }
    char line2[4096]; //create a temporary variable
    while (
        fscanf(ns, "%s %s", line, line2)
        != EOF) { //read line by line setting the first word to line and the second word to line2 until end of file
        bf_insert(bf, line);
        ht_insert(ht, line, line2);
    }

    char *word = NULL; //create a temporary variable
    bool flagone = false; //flag for thoughtcrime
    bool flagtwo = false; //flag for counseling
    Node *badlist = NULL; //create a list to hold my badspeak words
    Node *oldlist = NULL; //create a list to hold my oldspeak and newspeak translations
    while ((word = next_word(stdin, &re)) != NULL) { //while my next word using my regex is not null
        for (uint32_t i = 0; i < strlen(word); i++) { //make sure my word is lowercase
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word) == true) { //check if the word is in my badspeak list
            Node *meow = ht_lookup(ht, word); //lookup my word
            if (meow != NULL
                && meow->newspeak == NULL) { //if my word is not null and it's newspeak is null
                flagone = true;
                badlist = bst_insert(badlist, word, NULL); //insert my word into my badlist
            }
            if (meow != NULL
                && meow->newspeak != NULL) { //if my word is not null and it's newspeak is not null
                flagtwo = true;
                oldlist = bst_insert(oldlist, word,
                    meow->newspeak); //insert my word and it's translation into oldlist
            }
        }
    }
    if (stats == true) { //stats function
        printf("Average BST size: %lf\n", ht_avg_bst_size(ht));
        printf("Average BST height: %lf\n", ht_avg_bst_height(ht));
        double abranch = (double) branches / lookups;
        printf("Average branches traversed: %.6f\n", abranch);
        double hashload = 100 * ((double) ht_count(ht) / ht_size(ht));
        printf("Hash table load: %.6f%%\n", hashload);
        double bloomload = 100 * ((double) bf_count(bf) / bf_size(bf));
        printf("Bloom filter load: %.6f%%\n", bloomload);
        return 0;
    }

    if (flagone == true && flagtwo == true) { //if user is flagged for thoughtcrime and counseling
        printf("%s", mixspeak_message);
        bst_print(badlist);
        bst_print(oldlist);
    } else if (flagone == true) { //if user is flagged for thoughtcrime
        printf("%s", badspeak_message);
        bst_print(badlist);
    } else if (flagtwo == true) { //if user is flagged for counseling
        printf("%s", goodspeak_message);
        bst_print(oldlist);
    }
    //free and close everything
    fclose(bs);
    fclose(ns);
    bst_delete(&badlist);
    bst_delete(&oldlist);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
}
