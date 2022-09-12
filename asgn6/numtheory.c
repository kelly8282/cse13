#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"
#include "randstate.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t zero, tempb, tempa; //creating our mpz_t variables
    mpz_init(tempb); //initalizing all the variables
    mpz_init(tempa);
    mpz_set(tempa, a);
    mpz_set(tempb, b);
    mpz_init(zero);
    while (mpz_cmp(zero, tempb) != 0) { //while b != 0
        mpz_t temp;
        mpz_init(temp);
        mpz_set(temp, tempb); // temp = b
        mpz_mod(tempb, tempa, tempb); //tempb = tempa % tempb
        mpz_set(tempa, temp); // tempa = temp
        mpz_clear(temp); //clearing temp
    }
    mpz_set(d, tempa); //setting our output to tempa
    mpz_clear(zero); //clearing everything else
    mpz_clear(tempa);
    mpz_clear(tempb);
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t rone, rtwo, tone, ttwo, zero, final, one; //creating variables
    mpz_inits(rone, rtwo, tone, ttwo, zero, final, one, NULL); //initiallzing
    mpz_set(rone, n);
    mpz_set(rtwo, a);
    mpz_init_set_str(tone, "0", 0);
    mpz_init_set_str(one, "1", 0);
    mpz_init_set_str(ttwo, "1", 0);
    while (mpz_cmp(zero, rtwo) != 0) { //while r2 not 0
        mpz_t q;
        mpz_init(q);
        mpz_fdiv_q(q, rone, rtwo); //q = r1 / r2
        mpz_t temp; // temp variables for rtwo
        mpz_init(temp);
        mpz_set(temp, rtwo);
        mpz_submul(rone, q, rtwo); // r1 = r1- q times r2
        mpz_set(rtwo, rone); //r2 = r1
        mpz_set(rone, temp); //r1 = r2 thru temp variables
        mpz_set(temp, ttwo); //temp variables for t2
        mpz_submul(tone, q, ttwo); //t1 = t1 - q times t2
        mpz_set(ttwo, tone); //t2 = t1
        mpz_set(tone, temp); //t1 = t2 thro temp variable
        mpz_clear(temp); //clearing
        mpz_clear(q);
    }
    mpz_set(i, tone);
    if (mpz_cmp(rone, one) > 0) { //if r bigger than 1
        mpz_set(i, zero); //return no inverse
    }
    if (mpz_sgn(tone) == -1) { //if t smaller than 0
        mpz_add(final, tone, n); //final = t plus n
        mpz_set(tone, final); //setting t1 to final
        mpz_set(i, tone); //setting output to tone
    }
    mpz_clears(rone, rtwo, tone, ttwo, zero, final, one, NULL);
}
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p, zero, two, temp, tempe;
    mpz_inits(p, zero, temp, tempe, NULL); //tempe = exponent
    mpz_set(p, base);
    mpz_set(tempe, exponent);
    mpz_init_set_str(v, "1", 0);
    mpz_init_set_str(two, "2", 0);
    while (mpz_sgn(tempe) == 1) { //while tempe > 0
        mpz_set(temp, tempe); //set temp to tempe
        mpz_mod(temp, temp, two); //mod temp by 2
        if (mpz_cmp(temp, zero) != 0) { //check if temp is odd
            mpz_mul(v, v, p); //v = v times p
            mpz_mod(v, v, modulus); //v = v % modulus
        }
        mpz_mul(p, p, p); //p = p*p
        mpz_mod(p, p, modulus); //p = p % modulus
        mpz_fdiv_q(tempe, tempe, two); //d = d floor division 2
    }
    mpz_set(out, v); //setting out variable
    mpz_clears(v, p, zero, two, temp, tempe, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
    mp_bitcnt_t s = 0;
    mpz_t r, y, j, jcomp, ncomp, temp, zero, one, two, three, ntemp, a, mthree, stemp;
    mpz_inits(r, y, j, temp, jcomp, ncomp, zero, ntemp, mthree, three, a, stemp, NULL);
    mpz_init_set_str(one, "1", 0);
    mpz_init_set_str(three, "3", 0);
    mpz_init_set_str(two, "2", 0);
    mpz_sub(ntemp, n, one);
    if (mpz_cmp(n, zero) == 0 || mpz_cmp(n, one) == 0) { //test case for 0 and 1
        mpz_clears(
            r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, stemp, a, mthree, three, NULL);
        return false;
    }
    if (mpz_cmp(n, two) == 0 || mpz_cmp(n, three) == 0) { //test case for  2 and 3
        mpz_clears(
            r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, stemp, a, mthree, three, NULL);
        return true;
    }
    if (mpz_even_p(n) != 0) { //test case for even numbers
        mpz_clears(
            r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, stemp, a, mthree, three, NULL);
        return false;
    }
    while (mpz_sgn(temp) == 0) { //while temp == 0
        s = s + 1;
        mpz_tdiv_r_2exp(
            temp, ntemp, s); //get the remainder division of our temp ntemp/s and set that to temp
    }
    s = s
        - 1; //s = s - 1 because the way our while loop sets it will make our s by inaccurate by one
    mpz_init_set_ui(stemp, s); //setting my stemp to s
    mpz_tdiv_q_2exp(r, ntemp, s); //getting the r value by the quotient of ntemp and our s variable
    for (uint64_t i = 1; i <= iters; i++) {
        mpz_set(mthree, n);
        mpz_sub(mthree, n, three);
        mpz_urandomm(a, state, mthree); //creating our randomv a variable from 0 to n-3
        mpz_add(a, a, two); //since we starting at 0, add two
        pow_mod(y, a, r, n); //y = pow_mod(a,r,n)
        mpz_sub(jcomp, stemp, one); //jcomp = s-1
        mpz_sub(ncomp, n, one); //ncomp = n-1

        if (mpz_cmp(y, one) != 0 && mpz_cmp(y, ncomp) != 0) { //if y!= 1 and y!= ncomp
            mpz_set(j, one);
            while (
                mpz_cmp(j, jcomp) <= 0 && mpz_cmp(y, ncomp) != 0) { //while j <jcomp and y != ncomp
                pow_mod(y, y, two, n); //y = pow_mod(y,2,n)
                if (mpz_cmp(y, one) == 0) { //if y == 1
                    mpz_clears(r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, stemp, a, mthree,
                        three, NULL);
                    return false;
                }
                mpz_add(j, j, one);
            }
            if (mpz_cmp(y, ncomp) != 0) { //if y != ncomp
                mpz_clears(r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, stemp, a, mthree,
                    three, NULL);
                return false;
            }
        }
    }
    mpz_clears(r, temp, zero, one, two, y, j, ncomp, jcomp, ntemp, a, mthree, three, stemp, NULL);
    return true;
}
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t random, temp;
    mpz_inits(random, temp, NULL);
    while (is_prime(random, iters) == false) { //while the random variable isn't prime
        mpz_urandomb(random, state, bits); //creating a new random variable
        mpz_set(temp, random);
        size_t size = mpz_sizeinbase(temp, 2); //get the size of a base 2 bit of the random variable
        while (size < bits) { //while the size is not in our range
            mpz_urandomb(random, state, bits); //createw new random variable
            mpz_set(temp, random);
            size = mpz_sizeinbase(temp, 2);
        }
    }
    mpz_set(p, random); //set output to new prime number
    mpz_clears(random, temp, NULL);
}
