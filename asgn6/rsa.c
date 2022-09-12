#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"
#include <stdlib.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    uint64_t pupper = 0;
    uint64_t plower = 0;
    uint64_t pbits = 0;
    plower = nbits / 4;
    pupper = (3 * nbits) / 4;
    pbits = (random() % (pupper - plower + 1)
             + plower); //random number of bits for p from nbits/4 to (3*nbits)/4
    uint64_t qbits = nbits - pbits;
    pbits = pbits + 1;
    qbits = qbits + 1;
    make_prime(p, pbits, iters); //creating prime p
    make_prime(q, qbits, iters); //creating prime q
    mpz_mul(n, p, q);
    mpz_t one, temp, totient, ptemp, qtemp;
    mpz_inits(totient, temp, ptemp, qtemp, NULL);
    mpz_init_set_str(one, "1", 0);
    mpz_set(ptemp, p);
    mpz_set(qtemp, q);
    mpz_sub(ptemp, ptemp, one);
    mpz_sub(qtemp, qtemp, one);
    mpz_mul(totient, qtemp, ptemp); //setting totient to (p-1)*(q-1)
    mpz_urandomb(e, state, nbits); //random e
    gcd(temp, e, totient); //gcd e and totient
    while (mpz_cmp(temp, one) != 0) { //while our gcd isn't our coprime
        mpz_urandomb(e, state, nbits); //create another random e
        gcd(temp, e, totient); //gcd e and totient
    }
    mpz_clears(one, temp, totient, ptemp, qtemp, NULL);
}
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    gmp_fscanf(pbfile, "%s\n", username);
}
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t one, totient, ptemp, qtemp;
    mpz_inits(totient, ptemp, qtemp, NULL);
    mpz_init_set_str(one, "1", 0);
    mpz_set(ptemp, p);
    mpz_set(qtemp, q);
    mpz_sub(ptemp, ptemp, one); //ptemp = ptemp - 1
    mpz_sub(qtemp, qtemp, one); //qtemp = qtemp -1
    mpz_mul(totient, qtemp, ptemp); //totient = qtemp * ptemp
    mod_inverse(d, e, totient); //set output to modinverse of e and totient
    mpz_clears(one, totient, ptemp, qtemp, NULL);
}
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t m;
    mpz_inits(m, NULL);
    size_t k = mpz_sizeinbase(n, 2); //creating k with the formula provided
    k = k - 1;
    k = k / 8;
    uint8_t *block;
    block = (uint8_t *) calloc(k, sizeof(uint8_t)); //initializing block
    block[0] = 0xFF; //setting the first element
    uint8_t temp = 0;
    while ((temp = fread(block + 1, sizeof(uint8_t), k - 1, infile))
           > 0) { //while there are still bits
        mpz_import(m, temp + 1, 1, sizeof(block[0]), 1, 0, block); //convert the bytes read
        rsa_encrypt(m, m, e, n); //encrypt
        gmp_fprintf(outfile, "%Zx\n", m); //print
    }
    free(block);
    mpz_clears(m, NULL);
}
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t m;
    mpz_inits(m, NULL);
    size_t k = mpz_sizeinbase(n, 2); //creating k with the formula provided
    k = k - 1;
    k = k / 8;
    uint8_t *block;
    block = (uint8_t *) calloc(k, sizeof(uint8_t)); //initializing block
    uint64_t temp;
    while (gmp_fscanf(infile, "%Zx\n", m) > 0) { //while there are still bits
        rsa_decrypt(m, m, d, n); //decrypt message
        mpz_export(block, &temp, 1, sizeof(uint8_t), 1, 0, m); //convert bytes
        fwrite(block + 1, sizeof(uint8_t), temp - 1, outfile); //write bytes to outfile
    }
    free(block);
    mpz_clears(m, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n); //set t to the output of powmod s e n
    if (mpz_cmp(m, t) == 0) { //if it's 0 return true
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t);
        return false;
    }
}
