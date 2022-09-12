#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#define OPTIONS "i:o:n:hv"

int main(int argc, char **argv) {
    int opt = 0;
    bool verbose = false;
    bool help = false;
    bool nn = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pbfile;
    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        default: help = true; break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'i':
            infile = fopen(optarg, "r"); //open infile
            if (infile == NULL) {
                fprintf(stderr, "Error opening infile.\n");
                return 1;
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w"); //open outfile
            if (outfile == NULL) {
                fprintf(stderr, "Error opening outfile.\n");
                return 1;
            }
            break;
        case 'n':
            nn = true;
            pbfile = fopen(optarg, "r"); //open pbfile
            if (pbfile == NULL) {
                fprintf(stderr, "Error opening pbfile.\n");
                return 1;
            }
            break;
        }
    }
    if (nn == false) { //opening our pbfile if user didn't want to input a file
        pbfile = fopen("rsa.pub", "r"); //open pbfile
        if (pbfile == NULL) {
            fprintf(stderr, "Error opening pbfile.\n");
            fclose(pbfile);
            return 0;
        }
    }

    if (help == true) { //helper function
        printf("SYNOPSIS\n");
        printf("   Encrypts data using RSA encryption.\n");
        printf("   Encrypted data is decrypted by the decrypt program.\n");

        printf("\nUSAGE\n");
        printf("   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");

        printf("\nOPTIONS\n");
        printf("   -h              Display program help and usage.\n");
        printf("   -v              Display verbose program output.\n");
        printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
        printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
        printf("   -n pbfile       Public key file (default: rsa.pub).\n");
        return 0;
    }
    char name[32];
    mpz_t n, e, s, confirm;
    mpz_inits(n, e, s, confirm, NULL);
    rsa_read_pub(n, e, s, name, pbfile); //reading our public key
    mpz_set_str(confirm, name, 62); //setting our name to a mpz_t
    if (verbose == true) { //verbose function
        printf("%s\n", name);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    if (rsa_verify(confirm, s, e, n) == false) { //seeing if our name is our verified signature
        fprintf(stderr, "Signature does not match\n");
        return 0;
    }

    rsa_encrypt_file(infile, outfile, n, e); //encrypting the file
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n, e, s, confirm, NULL);
    return 0;
}
