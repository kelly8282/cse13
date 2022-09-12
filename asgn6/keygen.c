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
#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv) {
    int opt = 0;
    uint64_t seed = time(NULL); //setting our default seed
    bool verbose = false;
    bool help = false;
    uint64_t bits = 256; //setting our default bits
    uint64_t iters = 50; //setting our default iters
    bool nn = false;
    bool dd = false;
    FILE *pbfile;
    FILE *pvfile;
    while ((opt = getopt(argc, argv, OPTIONS))
           != -1) { //using getopt to see which test cases are ran by user
        switch (opt) { //test cases
        default: help = true; break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'b': bits = atoi(optarg); break;
        case 'i': iters = atoi(optarg); break;
        case 'n':
            nn = true;
            pbfile = fopen(optarg, "w"); //open pbfile
            if (pbfile == NULL) {
                fprintf(stderr, "Error opening pbfile.\n");
                fclose(pbfile);
                return 0;
            }
            break;
        case 'd':
            dd = true;
            pvfile = fopen(optarg, "w"); //open pvfile
            if (pvfile == NULL) {
                fprintf(stderr, "Error opening pvfile.\n");
                fclose(pvfile);
                return 1;
            }
            break;
        case 's': seed = atoi(optarg); break;
        }
    }

    if (nn == false) { //open our pbfile if user didn't want to input a file
        pbfile = fopen("rsa.pub", "w"); //open pbfile
        if (pbfile == NULL) {
            fprintf(stderr, "Error opening pbfile.\n");
            fclose(pbfile);
            return 0;
        }
    }
    if (dd == false) { //open our pvfile if user didn't want to input a file
        pvfile = fopen("rsa.priv", "w"); //open pvfile
        if (pvfile == NULL) {
            fprintf(stderr, "Error opening pvfilefile.\n");
            fclose(pvfile);
            return 0;
        }
    }
    if (help == true) { //helper function
        printf("SYNOPSIS\n");
        printf("  Generates an RSA public/private key pair.\n");

        printf("USAGE\n");
        printf("  ./keygen [-hv] [-b bits] -i iters -n pbfile -d pvfile \n");

        printf("OPTIONS\n");
        printf("  -h             Display program usage and help.\n");
        printf("  -v             Display verbose output program.\n");
        printf("  -b bits        Minimum bits needed for public key n.\n");
        printf("  -i iters       Miller-Rabin iterations for testing primes (default: 50).\n");
        printf("  -n pbfile      Public key file (default: rsa.pub).\n");
        printf("  -d pvfile      Private key file (default: rsa. priv).\n");
        printf("  -s seed        Random seed for testing.\n");
        return 0;
    }
    fchmod(fileno(pvfile), 0600); //setting file permissions
    randstate_init(seed); //initializing our state to our seed
    mpz_t p, signature, d, q, n, e, username;
    mpz_inits(p, q, d, n, e, signature, username, NULL);
    rsa_make_pub(p, q, n, e, bits, iters); //making public key
    rsa_make_priv(d, e, p, q); //making private key
    char *name;
    name = getenv("USER"); //getting the user's name as a string
    mpz_set_str(username, name, 62); //converting our name into a mpz_t
    rsa_sign(signature, username, d, n); //using rsa_sign to compute the signature of the username
    rsa_write_pub(n, e, signature, name, pbfile); //writing public key to the public file
    rsa_write_priv(n, d, pvfile); //writing the private key to our file
    if (verbose == true) { //verbose function
        printf("%s\n", name);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(signature, 2), signature);
        gmp_printf("p (%zu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%zu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(p, signature, d, q, n, e, username, NULL);
    return 0;
}
