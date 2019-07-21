#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * We only want to consider ASCII characters from 32 to 127.
 */
#define ASCII_START 32
#define ASCII_END 127

/**
 * Generate a Caesar cipher with a random offset.  The index represents the input character, and the value represents the output character.
 * @return A character array representing our Caesar cipher.
 */
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

/**
 * Generate a completely randomized cipher.  The index represents the input character, and the value represents the output character.
 * @return A character array representing our random cipher.
 */
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

/**
 * Create a decipher based on a cipher and return it.
 * @param cipher The cipher we used to encrypt.
 * @return The decipher we use to decrypt.
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

/**
 * Encrypt a character with a specified cipher.
 * @param c The character to encrypt.
 * @param cipher The cipher we use.
 * @return The encrypted character.
 */
char encryptChar(char c, char *cipher) {
    return cipher[c - ASCII_START];
}

/**
 * Decrypt a character with a specified decipher.
 * @param c The character to decrypt.
 * @param decipher The decipher we use.
 * @return The decrypted character.
 */
char decryptChar(char c, char *decipher) {
    return decipher[c - ASCII_START];
}

/**
 * Do all our encryption with specified input/output files.
 * @param inputFileName The text file we want to encrypt.
 * @param outputFileName The encrypted text file.
 * @param cipherFileName The file we want to output our cipher to.
 * @param cipherType The type of cipher we want to use.  Anything other than "caesar" will be assumed as random.
 */
void handleEncryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName, char const* cipherType) {
    char* cipher;
    if (strcmp(cipherType, "caesar") == 0)
        cipher = randomCaesarCipher();
    else
        cipher = randomizedCipher();
    FILE* cipherOut = fopen(cipherFileName, "w");
    int n = ASCII_END - ASCII_START;
    int i;
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

/**
 * Do all our decryption with specified input/output files.
 * @param inputFileName The text file we want to decrypt.
 * @param outputFileName The decrypted text file.
 * @param cipherFileName The cipher we used to encrypt the file.
 */
void handleDecryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName) {
    int n = ASCII_END - ASCII_START;
    char* cipher = malloc(sizeof(char) * n);
    FILE* cipherFile = fopen(cipherFileName, "r");
    if (cipherFile == NULL) {
        perror("Error opening cipher file.\n");
        exit(EXIT_FAILURE);
    }
    //Read cipher from file
    fgets(cipher, n, cipherFile);
    char* decipher = getDecipher(cipher);
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