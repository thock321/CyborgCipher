/**
 * @file ccipher.h
 * @brief Function prototypes for Cyborg Cipher.
 * @author Albert Yang
 */

#ifndef CYBORGCIPHER_CCIPHER_H
#define CYBORGCIPHER_CCIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * We only want to consider ASCII characters from 32 (inc) to 127 (exc).
 * Since our char values only go up to 126, we don't need to use unsigned chars.
 */
#define ASCII_START 32
#define ASCII_END 127

/**
 * Generate a Caesar cipher with a random offset.  The index represents the input character, and the value represents the output character.
 * @return A character array representing our Caesar cipher.
 */
char* randomCaesarCipher();

/**
 * Generate a completely randomized cipher.  The index represents the input character, and the value represents the output character.
 * @return A character array representing our random cipher.
 */
char* randomizedCipher();

/**
 * Create a decipher based on a cipher and return it.
 * @param cipher The cipher we used to encrypt.
 * @return The decipher we use to decrypt.
 */
char* getDecipher(char const* cipher);

/**
 * Encrypt a character with a specified cipher.
 * @param c The character to encrypt.
 * @param cipher The cipher we use.
 * @return The encrypted character.
 */
char encryptChar(char const c, char const *cipher);

/**
 * Decrypt a character with a specified decipher.
 * @param c The character to decrypt.
 * @param decipher The decipher we use.
 * @return The decrypted character.
 */
char decryptChar(char const c, char const *decipher);

/**
 * Ensure that a pointer is not a null value.  If it is, print the specified error message.
 * @param ptr The pointer to verify.
 * @param errorMsg The error message to print.
 */
void assertNotNull(void* ptr, char const* errorMsg);

/**
 * Do all our encryption with specified input/output files.
 * @param inputFileName The text file we want to encrypt.
 * @param outputFileName The encrypted text file.
 * @param cipherFileName The file we want to output our cipher to.
 * @param cipherType The type of cipher we want to use.  Anything other than "caesar" will be assumed as random.
 */
void handleEncryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName, char const* cipherType);

/**
 * Do all our decryption with specified input/output files.
 * @param inputFileName The text file we want to decrypt.
 * @param outputFileName The decrypted text file.
 * @param cipherFileName The cipher we used to encrypt the file.
 */
void handleDecryption(char const* inputFileName, char const* outputFileName, char const* cipherFileName);

#endif //CYBORGCIPHER_CCIPHER_H
