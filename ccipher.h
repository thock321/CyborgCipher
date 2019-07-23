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

//First 32 ASCII characters are control codes, which are not printable, writeable or readable.  We can ignore those.
#define ASCII_START 32
#define ASCII_MAX 256

/**
 * Generate a Caesar cipher with a random offset.  The index represents the input unsigned character, and the value represents the output unsigned character.
 * @return A unsigned character array representing our Caesar cipher.
 */
unsigned char* randomCaesarCipher();

/**
 * Generate a completely (pseudo) randomized cipher.  The index represents the input unsigned character, and the value represents the output unsigned character.
 * Shuffling algorithm credits to Ben Pfaff.  https://benpfaff.org/writings/clc/shuffle.html
 * @return A unsigned character array representing our random cipher.
 */
unsigned char* randomizedCipher();

/**
 * Create a decipher based on a cipher and return it.
 * @param cipher The cipher we used to encrypt.
 * @return The decipher we use to decrypt.
 */
unsigned char* getDecipher(unsigned char const* cipher);

/**
 * Encrypt a unsigned character with a specified cipher.
 * @param c The unsigned character to encrypt.
 * @param cipher The cipher we use.
 * @return The encrypted unsigned character.
 */
unsigned char encryptChar(unsigned char const c, unsigned char const *cipher);

/**
 * Decrypt a unsigned character with a specified decipher.
 * @param c The unsigned character to decrypt.
 * @param decipher The decipher we use.
 * @return The decrypted unsigned character.
 */
unsigned char decryptChar(unsigned char const c, unsigned char const *decipher);

/**
 * Ensure that a pointer is not a null value.  If it is, print the specified error message.
 * @param ptr The pointer to verify.
 * @param errorMsg The error message to print.
 */
void assertNotNull(void* ptr, unsigned char const* errorMsg);

/**
 * Do all our encryption with specified input/output files.
 * @param inputFileName The text file we want to encrypt.
 * @param outputFileName The encrypted text file.
 * @param cipherFileName The file we want to output our cipher to.
 * @param cipherType The type of cipher we want to use.  Anything other than "caesar" will be assumed as random.
 */
void handleEncryption(unsigned char const* inputFileName, unsigned char const* outputFileName, unsigned char const* cipherFileName, unsigned char const* cipherType);

/**
 * Do all our decryption with specified input/output files.
 * @param inputFileName The text file we want to decrypt.
 * @param outputFileName The decrypted text file.
 * @param cipherFileName The cipher we used to encrypt the file.
 */
void handleDecryption(unsigned char const* inputFileName, unsigned char const* outputFileName, unsigned char const* cipherFileName);

#endif //CYBORGCIPHER_CCIPHER_H
