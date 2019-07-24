# Cyborg Cipher

A program that can encrypt and decrypt text based on a cipher.

All ASCII characters, except control codes, are supported. (32 to 255)

Please note that this program is only guaranteed to run on Windows 10 machines.

## Getting Started

### Prerequisites

#### Windows

Please make sure to have Visual Studio Developer Command Prompt installed.  Using the Developer	Command Prompt, navigate to the folder containing `main.c` and execute:

```
cl ccipher.c main.c
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

## Features

Currently, a random offset Caesar cipher and a fully (pseduo) randomized cipher is supported.  To specify using the Caesar cipher, use `caesar` as the third argument.

### Windows

```
ccipher.exe cipher caesar
```

A blank third argument or any other value will result in the default randomized cipher being used.

## Extra Notes

### Thought Process

The most basic cipher is probably the Caesar cipher.  However, a slightly better cipher would be a pseudo-randomized cipher.

When encrypting and decrypting the files, my program reads and writes characters one at a time.  The reason for going this route rather than reading the files into a buffer is to handle the case if our input file is very large.  Storing a very large input into memory would not be feasible.

Since ASCII control codes can't be read or written properly, the program completely ignores them.