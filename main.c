/**
 * @file main.c
 * @brief Main driver for Cyborg Cipher.
 * @author Albert Yang
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ccipher.h"

/**
 * Start program.
 * @param argc Number of arguments + 1.
 * @param argv First value is name of program, subsequent values are program arguments.
 * @return Should not return.
 */
int main(int argc, char** argv) {
    //Seed RNG based on time
    srand(time(NULL));
    if (argc < 2) {
        perror("Please specify mode.  Use argument 'cipher' for cipher mode, and 'decipher' for decipher mode.");
        exit(EXIT_FAILURE);
    }
    char* mode = argv[1];
    if (strcmp(mode, "cipher") == 0) {
        handleEncryption("input.txt", "encrypted.txt", "cipher.txt", argc >= 3 ? argv[2] : "random");
    } else if (strcmp(mode, "decipher") == 0) {
        handleDecryption("encrypted.txt", "decrypted.txt", "cipher.txt");
    }
    return 0;
}