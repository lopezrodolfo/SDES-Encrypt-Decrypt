# Simplified DES Encryption/Decryption

This project implements a Simplified Data Encryption Standard (SDES) algorithm for file encryption and decryption.

## Author

Rodolfo Lopez

## Date

October 6, 2020

## Files

- `simplified_des.h`: Header file containing function declarations for the SDES algorithm

- `simplified_des.c`: Implementation of the SDES algorithm functions

- `sdes-encrypt.c`: Program to encrypt files using SDES

- `sdes-decrypt.c`: Program to decrypt files using SDES

- `Makefile`: Compilation instructions for the project

- `unencrypted_files/`: Directory containing sample unencrypted files

## Compilation

To compile the programs, run:

`make`

This will produce the `sdes-encrypt` and `sdes-decrypt` executables.

## Usage

### Encryption

```
./sdes-encrypt -k <key> -n <rounds> -o <output_file> <input_file>
```

- `<key>`: 9-bit encryption key in hexadecimal (e.g. 0x1AB)

- `<rounds>`: Number of encryption rounds (1-9)

- `<output_file>`: Path to write encrypted output

- `<input_file>`: File to encrypt

#### Examples

```
./sdes-encrypt -k 0x08A -n 2 -o encrypted_file.txt unencrypted_files/small_text.txt
```

```
./sdes-encrypt -k 0x04C -n 8 -o encrypted_file.txt unencrypted_files/bigger_text.txt
```

### Decryption

```
./sdes-decrypt -k <key> -n <rounds> -o <output_file> <input_file>
```

Parameters are the same as for encryption.

#### Examples

```
./sdes-decrypt -k 0x08A -n 2 -o decrypted_file.txt encrypted_file.txt
```

```
./sdes-decrypt -k 0x04C -n 8 -o decrypted_file.txt encrypted_file.txt
```

## Algorithm Details

This implements a simplified version of DES with the following characteristics:

- 12-bit block size (vs 64-bit in full DES)

- 9-bit master key (vs 56-bit in full DES)

- Configurable number of rounds (1-9)

- Simplified key schedule and Feistel function

## Acknowledgements

Professor Sat Garcia wrote the starter code and I implemented the functions in simplified_des.c
and I finished implementing the decrypt_file function in sdes-decrypt.c
