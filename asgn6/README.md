# Assignment 6: Public Key Cryptography

## Description
In this program, we are making a program that creates some math functions that allow us to make public and private keys that lets us encrypt and decrypt files.

## Building  
Run this command to compile the program
```
$ make all
```

## Running/Instructions
Run this command to test/see the followings.
```
$ ./encrypt
```
You can run whatever command you wish after the following code above. Note: -h will give you a menu.

```
$ ./decrypt
```
You can run whatever command you wish after the following code above. Note -h will give you a menu.

```
$ ./keygen
```
You can run whatever command you wish after the following code above. Note -h will give you a menu.

## File Included
numtheory.c- A source file for implementing of my functions.  
numtheory.h- A header file that specifies the interface for numtheory.c.  
randstate.c- A source file for implementing the random state interface of my RSA and numtheory functions.  
randstate.h- A header file that resets and initializes my random state.  
rsa.c- A source file for implementing my RSA library.  
rsa.h- A header file that specifies the interface for rsa.c.  
encrypt.c- A source file for my encrypt program.  
decrypt.c- A source file for my decrypt program.  
keygen.c- A source file for my keygen program.  
Makefile- This allows us to use clang and compile our program.  
README.md- In markdown format, it tells us how to run the program and how the program was made.  
DESIGN.pdf- This is how I started thinking about how to code the program.  
