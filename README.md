# Cyborg Cipher

A program that can encrypt and decrypt text based on a cipher.

Only ASCII characters with values 32 (inclusive) to 127 (exclusive) are supported.

## Getting Started

### Prerequisites

#### Windows

Please make sure to have Visual Studio Developer Command Prompt installed.  Using the Developer	Command Prompt, navigate to the folder containing `main.c` and execute:

```
cl main.c
```

To compile.

#### Linux

TODO

## Running tests

Create a file called `input.txt` in the same directory as `main.exe`.  Then run:

```
main.exe cipher
```

To encrypt the file.  Run:

```
main.exe decipher
```

To decrypt the encrypted file.

## Features

Currently, a random offset Caesar cipher and a fully randomized cipher is supported.  To specify using the Caesar cipher, use `caesar` as the third argument.

```
main.exe cipher caesar
```

A blank third argument or any other value will result in the default randomized cipher being used.

## Extra Notes

### Thought Process

The most basic cipher is probably the Caesar cipher.  However, a slightly better cipher would be a fully randomized cipher.

When encrypting and decrypting the files, my program reads and writes characters one at a time.  The reason for going this route rather than reading the files into a buffer is to handle the case if our input file is very large.  Storing a very large input into memory would not be feasible.

### Edge Cases Tested