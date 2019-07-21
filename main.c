#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ASCII_START 32
#define ASCII_END 127

/*
 *
 */
char* randomCaesarCipher() {
    int n = ASCII_END - ASCII_START;
    int offset = rand() % ASCII_END;
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
        char temp = cipher[i];
        cipher[i] = cipher[j];
        cipher[j] = temp;
    }
    return cipher;
}

/*
 * Create a decipher based on a cipher and return it.
 *
 */
char* getDecipher(char const* cipher) {
    int n = ASCII_END - ASCII_START;
    char* decipher = (char*) malloc(sizeof(char) * n);
    int i;
    for (i = 0; i < n; i++) {
        decipher[cipher[i] - ASCII_START] = i + ASCII_START;
    }
    return decipher;
}

char encryptChar(char c, char *cipher) {
    return cipher[c - ASCII_START];
}

char decryptChar(char c, char *decipher) {
    return decipher[c - ASCII_START];
}

void handleEncryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName, char const* cipherType) {
    char* cipher;
    if (strcmp(cipherType, "caesar") == 0)
        cipher = randomCaesarCipher();
    else
        cipher = randomizedCipher();
    int i;
    FILE* cipherOut = fopen(cipherFileName, "w");
    int n = ASCII_END - ASCII_START;
    for (i = 0; i < n; i++) {
        fprintf(cipherOut, "%c", cipher[i]);
    }
    FILE* input = fopen(inputFileName, "r");
    if (input == NULL) {
        perror("Error opening input file.\n");
        exit(EXIT_FAILURE);
    }
    FILE* out = fopen(outputFileName, "w");
    if (out == NULL) {
        perror("Error writing to output file.\n");
        exit(EXIT_FAILURE);
    }
    char c;
    while ((c = fgetc(input)) != EOF) {
        c = encryptChar(c, cipher);
        fprintf(out, "%c", c);
    }
    fclose(cipherOut);
    fclose(input);
    fclose(out);
    free(cipher);
    printf("Successfully encrypted.");
}

void handleDecryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName) {
    FILE* cipherFile = fopen(cipherFileName, "r");
    if (cipherFile == NULL) {
        perror("Error opening cipher file.\n");
        exit(EXIT_FAILURE);
    }
    int n = ASCII_END - ASCII_START;
    char* cipher = malloc(sizeof(char) * n);
    fgets(cipher, n, cipherFile);
    char* decipher = getDecipher(cipher);
    free(cipher);
    FILE* input = fopen(inputFileName, "r");
    if (input == NULL) {
        perror("Error opening encrypted file.\n");
        exit(EXIT_FAILURE);
    }
    FILE* out = fopen(outputFileName, "w");
    if (out == NULL) {
        perror("Error writing to decrypted file.");
        exit(EXIT_FAILURE);
    }
    char c;
    while ((c = fgetc(input)) != EOF) {
        c = decryptChar(c, decipher);
        fprintf(out, "%c", c);
    }
    fclose(input);
    fclose(out);
    fclose(cipherFile);
    free(decipher);
    printf("Successfully decrypted.");
}

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