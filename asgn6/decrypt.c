#include "rsa.h"
#include <stdio.h>
#include <gmp.h>
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
    FILE *pvfile;
    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        default: help = true; break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) { //opening infile
                fprintf(stderr, "Error opening infile.\n");
                return 1;
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w"); //opening outfile
            if (outfile == NULL) {
                fprintf(stderr, "Error opening outfile.\n");
                return 1;
            }
            break;
        case 'n':
            nn = true;
            pvfile = fopen(optarg, "r"); //opening pvfile
            if (pvfile == NULL) {
                fprintf(stderr, "Error opening pvfile.\n");
                return 1;
            }
            break;
        }
    }
    if (nn == false) { //opening our pvfile if the user didn't want to input a file
        pvfile = fopen("rsa.priv", "r"); //opening pvfile
        if (pvfile == NULL) {
            fprintf(stderr, "Error opening pvfile.\n");
            fclose(pvfile);
            return 0;
        }
    }

    if (help == true) { //helper function
        printf("SYNOPSIS\n");
        printf("   Decrypts data using RSA decryption.\n");
        printf("   Encrypted data is encrypted by the encrypt program.\n");

        printf("\nUSAGE\n");
        printf("   ./decrypt [-hv] [-i infile] [-o outfile] -d privkey\n");

        printf("\nOPTIONS\n");
        printf("   -h              Display program help and usage.\n");
        printf("   -v              Display verbose program output.\n");
        printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
        printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
        printf("   -d pvfile       Private key file (default: rsa.priv).\n");
        return 0;
    }

    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, pvfile); //reding our private key
    if (verbose == true) { //verbose function
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    rsa_decrypt_file(infile, outfile, n, d); //decrypt file
    fclose(pvfile);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n, d, NULL);
    return 0;
}
