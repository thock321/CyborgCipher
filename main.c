#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ASCII_START 32
#define ASCII_END 127

/*
 *
 */
char* generateCipher() {
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

char encrypt(char c, char* cipher) {
    return cipher[c - ASCII_START];
}

char decrypt(char c, char* decipher) {
    return decipher[c - ASCII_START];
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

        char *cipher = generateCipher();

        int i;
        FILE* cipherOut = fopen("cipher.txt", "w");
        int n = ASCII_END - ASCII_START;
        for (i = 0; i < n; i++) {
            fprintf(cipherOut, "%c", cipher[i]);
        }
        fclose(cipherOut);

        FILE* input = fopen("input.txt", "r");
        if (input == NULL) {
            perror("Error opening input file.\n");
            exit(EXIT_FAILURE);
        }
        FILE* out = fopen("encrypted.txt", "w");
        if (out == NULL) {
            perror("Error writing to output file.\n");
            exit(EXIT_FAILURE);
        }
        char c;
        while ((c = fgetc(input)) != EOF) {
            c = encrypt(c, cipher);
            fprintf(out, "%c", c);
        }
        printf("Successfully encrypted.");
        fclose(input);
        fclose(out);
        free(cipher);
    } else if (strcmp(mode, "decipher") == 0) {
        FILE* cipherFile = fopen("cipher.txt", "r");
        if (cipherFile == NULL) {
            perror("Error opening cipher file.\n");
            exit(EXIT_FAILURE);
        }
        int n = ASCII_END - ASCII_START;
        char* cipher = malloc(sizeof(char) * n);
        fgets(cipher, n, cipherFile);
        char* decipher = getDecipher(cipher);
        free(cipher);
        FILE* input = fopen("encrypted.txt", "r");
        if (input == NULL) {
            perror("Error opening encrypted file.\n");
            exit(EXIT_FAILURE);
        }
        FILE* out = fopen("decrypted.txt", "w");
        if (out == NULL) {
            perror("Error writing to decrypted file.");
            exit(EXIT_FAILURE);
        }
        char c;
        printf("%s", decipher);
        while ((c = fgetc(input)) != EOF) {
            c = decrypt(c, decipher);
            fprintf(out, "%c", c);
        }
        fclose(input);
        fclose(out);
        fclose(cipherFile);
        free(decipher);
        printf("Successfully decrypted.");
    }
    return 0;
}