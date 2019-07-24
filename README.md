# Cyborg Cipher

A program that can encrypt and decrypt text based on a cipher.

All ASCII characters, except control codes, are supported. (32 to 255)

Please note that this program has only been tested on Windows 10 and Ubuntu, and thus only guaranteed for those two operating systems.

## Getting Started

### Prerequisites

#### Windows

Please make sure to have Visual Studio Developer Command Prompt installed.  Using the Developer	Command Prompt, navigate to the folder containing `main.c` and execute:

```
cl ccipher.c main.c
```

To compile.

#### Linux

Please make sure `gcc` is installed.  Run:

```
gcc ccipher.c main.c -o ccipher
```

To compile.

## Running tests

### Windows

Create a file called `input.txt` in the same directory as `main.exe`.  Then run:

```
ccipher.exe cipher
```

To encrypt the file.  Run:

```
ccipher.exe decipher
```

To decrypt the encrypted file.

### Linux

Create a file called `input.txt` in the same directory as `main.exe`.  Then run:

```
./ccipher cipher
```

To encrypt the file.  Run:

```
./ccipher decipher
```

To decrypt the encrypted file.

## Features

Currently, a random offset Caesar cipher and a fully (pseduo) randomized cipher is supported.  To specify using the Caesar cipher, use `caesar` as the third argument.

### Windows

```
ccipher.exe cipher caesar
```

### Linux

```
./ccipher cipher caesar
```

A blank third argument or any other value will result in the default randomized cipher being used.

## Extra Notes

### Thought Process

The most basic cipher is probably the Caesar cipher.  However, a slightly better cipher would be a pseudo-randomized cipher.

When encrypting and decrypting the files, my program reads and writes characters one at a time.  The reason for going this route rather than reading the files into a buffer is to handle the case if our input file is very large.  Storing a very large input into memory would not be feasible.

Since ASCII control codes can't be read or written properly, the program completely ignores them.  Only the new line character is supported.  

### Possible Improvements

The new line character could be a part of the cipher as well.  This helps obfuscate the encrypted message to make it harder to decrypt without the cipher.  However, I felt that this was an unncessary complication for the exercise, especially given the way I decided to design how the ciphers are represented in memory, and how simple the ciphers are.  

Rather than storing the characters of the cipher into a file, I could store their byte representations.  This would also solve the above issue, since my program will not need to ignore control code characters since they can't be written properly.  Their byte representations can be written fine.

The ciphers could be made more complex through a series of transformations on the ciphers, such as transposing etc.