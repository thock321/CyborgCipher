/**
 * @file ccipher.c
 * @brief Function implementations for Cyborg Cipher.
 * @author Albert Yang
 */

#include "ccipher.h"

char* randomCaesarCipher() {
    int n = ASCII_END - ASCII_START;
    //Randomized offset to shift the characters by.
    int offset = rand() % ASCII_END;
    //A 0 offset essentially means no encryption.
    if (offset == 0)
        offset = 1;
    char* cipher = (char*) malloc(sizeof(char) * n);
    int i;
    for (i = ASCII_START; i < ASCII_END; i++) {
        cipher[i - ASCII_START] = ((i + offset) % n) + ASCII_START;
    }
    return cipher;
}

char* randomizedCipher() {
    int n = ASCII_END - ASCII_START;
    char* cipher = (char*) malloc(sizeof(char) * n);
    int i;
    for (i = 0; i < n; i++) {
        cipher[i] = i + ASCII_START;
    }
    for (i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        //Use temp switch instead of XOR switch in case cipher[i] == cipher[j]
        char temp = cipher[i];
        cipher[i] = cipher[j];
        cipher[j] = temp;
    }
    return cipher;
}

char* getDecipher(char const* cipher) {
    int n = ASCII_END - ASCII_START;
    char* decipher = (char*) malloc(sizeof(char) * n);
    int i;
    for (i = 0; i < n; i++) {
        decipher[cipher[i] - ASCII_START] = i + ASCII_START;
    }
    return decipher;
}

char encryptChar(char const c, char const *cipher) {
    return cipher[c - ASCII_START];
}

char decryptChar(char const c, char const *decipher) {
    return decipher[c - ASCII_START];
}

void assertNotNull(void* ptr, char const* errorMsg) {
    if (ptr == NULL) {
        perror(errorMsg);
        exit(EXIT_FAILURE);
    }
}

void handleEncryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName, char const* cipherType) {
    char* cipher;
    if (strcmp(cipherType, "caesar") == 0)
        cipher = randomCaesarCipher();
    else
        cipher = randomizedCipher();
    FILE* cipherOut = fopen(cipherFileName, "w");
    assertNotNull(cipherOut, "Error writing to cipher file.\n");
    int n = ASCII_END - ASCII_START;
    int i;
    for (i = 0; i < n; i++) {
        fprintf(cipherOut, "%c", cipher[i]);
    }
    FILE* input = fopen(inputFileName, "r");
    assertNotNull(input, "Error opening input file.\n");
    FILE* out = fopen(outputFileName, "w");
    assertNotNull(out, "Error writing to output file.\n");
    char c;
    //Encrypt
    while ((c = fgetc(input)) != EOF) {
        c = encryptChar(c, cipher);
        fprintf(out, "%c", c);
    }
    //Cleanup
    fclose(cipherOut);
    fclose(input);
    fclose(out);
    free(cipher);
    printf("Successfully encrypted.");
}

void handleDecryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName) {
    int n = ASCII_END - ASCII_START;
    char* cipher = malloc(sizeof(char) * n);
    FILE* cipherFile = fopen(cipherFileName, "r");
    assertNotNull(cipherFile, "Error opening cipher file.\n");
    //Read cipher from file
    fgets(cipher, n, cipherFile);
    char* decipher = getDecipher(cipher);
    FILE* input = fopen(inputFileName, "r");
    assertNotNull(input, "Error opening encrypted file.\n");
    FILE* out = fopen(outputFileName, "w");
    assertNotNull(out, "Error writing to decrypted file.\n");
    char c;
    //Decrypt
    while ((c = fgetc(input)) != EOF) {
        c = decryptChar(c, decipher);
        fprintf(out, "%c", c);
    }
    fclose(input);
    fclose(out);
    fclose(cipherFile);
    free(decipher);
    free(cipher);
    printf("Successfully decrypted.");
}