/**
 * @file ccipher.c
 * @brief Function implementations for Cyborg Cipher.
 * @author Albert Yang
 */

#include "ccipher.h"

unsigned char* randomCaesarCipher() {
    int n = ASCII_MAX - ASCII_START;
    //Randomized offset to shift the unsigned characters by.
    int offset = rand() % ASCII_MAX;
    //A 0 offset essentially means no encryption.
    if (offset == 0)
        offset = 1;
    unsigned char* cipher = (unsigned char*) malloc(sizeof(unsigned char) * n);
    int i;
    for (i = ASCII_START; i < ASCII_MAX; i++) {
        cipher[i - ASCII_START] = ((i + offset) % n) + ASCII_START;
    }
    return cipher;
}

unsigned char* randomizedCipher() {
    int n = ASCII_MAX - ASCII_START;//ASCII_END - ASCII_START;
    unsigned char* cipher = (unsigned char*) malloc(sizeof(unsigned char) * n);
    int i;
    for (i = 0; i < n; i++) {
        cipher[i] = i + ASCII_START;
    }
    //Shuffling algorithm is based on this link: https://benpfaff.org/writings/clc/shuffle.html
    for (i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        //Use temp switch instead of XOR switch in case cipher[i] == cipher[j]
        unsigned char temp = cipher[i];
        cipher[i] = cipher[j];
        cipher[j] = temp;
    }
    return cipher;
}

unsigned char* getDecipher(unsigned char const* cipher) {
    int n = ASCII_MAX - ASCII_START;//ASCII_END - ASCII_START;
    unsigned char* decipher = (unsigned char*) malloc(sizeof(unsigned char) * n);
    int i;
    for (i = 0; i < n; i++) {
        decipher[cipher[i] - ASCII_START] = i + ASCII_START;
    }
    return decipher;
}

unsigned char encryptChar(unsigned char const c, unsigned char const *cipher) {
    return cipher[(unsigned char) (c - ASCII_START)];
}

unsigned char decryptChar(unsigned char const c, unsigned char const *decipher) {
    return decipher[(unsigned char) (c - ASCII_START)];
}

void assertNotNull(void* ptr, unsigned char const* errorMsg) {
    if (ptr == NULL) {
        perror(errorMsg);
        exit(EXIT_FAILURE);
    }
}

void handleEncryption(unsigned char const* inputFileName, unsigned char const* outputFileName, unsigned char const* cipherFileName, unsigned char const* cipherType) {
    unsigned char* cipher;
    if (strcmp(cipherType, "caesar") == 0)
        cipher = randomCaesarCipher();
    else
        cipher = randomizedCipher();
    FILE* cipherOut = fopen(cipherFileName, "w");
    assertNotNull(cipherOut, "Error writing to cipher file.\n");
    int n = ASCII_MAX - ASCII_START;
    fwrite(cipher, sizeof(unsigned char), n, cipherOut);
    FILE* input = fopen(inputFileName, "r");
    assertNotNull(input, "Error opening input file.\n");
    FILE* out = fopen(outputFileName, "w");
    assertNotNull(out, "Error writing to output file.\n");
    int c;
    //Encrypt
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            fputc('\n', out);
            continue;
        }
        c = encryptChar(c, cipher);
        fputc(c, out);
    }
    //Cleanup
    fclose(cipherOut);
    fclose(input);
    fclose(out);
    free(cipher);
    printf("Successfully encrypted.\n");
}

void handleDecryption(unsigned char const* inputFileName, unsigned char const* outputFileName, unsigned char const* cipherFileName) {
    int n = ASCII_MAX - ASCII_START;
    unsigned char* cipher = malloc(sizeof(unsigned char) * n);
    FILE* cipherFile = fopen(cipherFileName, "r");
    assertNotNull(cipherFile, "Error opening cipher file.\n");
    //Read cipher from file
    int i;
    for (i = 0; i < n; i++) {
        unsigned char ch = fgetc(cipherFile);
        cipher[i] = ch;
    }
    unsigned char* decipher = getDecipher(cipher);
    FILE* input = fopen(inputFileName, "r");
    assertNotNull(input, "Error opening encrypted file.\n");
    FILE* out = fopen(outputFileName, "w");
    assertNotNull(out, "Error writing to decrypted file.\n");
    int c;
    //Decrypt
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            fputc('\n', out);
            continue;
        }
        c = decryptChar(c, decipher);
        fputc(c, out);
    }
    fclose(input);
    fclose(out);
    fclose(cipherFile);
    free(decipher);
    free(cipher);
    printf("Successfully decrypted.\n");
}