# Rank-Based ABE PKE

## Introduction

This scheme is based on Rollo-II and add a layer of ABE using cipher text policy with bloom filters.
In this implementation, the RBC-Lib is used.

## Installation

Warning, you will first need to download the rbclib and compile it to obtain librbc.a and librbc-nist.a files.

Clone this repo, copy `librbc.c` and `librbc-nist.a` into `lib/rbc_lib` and run:

```bash
make
```

You can also run unit tests with:

```bash
make test
```

## Usage

To generate the Public and Private Keys:

```bash
./abepke keygen <public_key_file> <private_key_file>
```

To encrypt data:

```bash
./abepke encrypt <public_key_file> <attributes_file> <plaintext_file> <cipher_file>
```

To decrypt data:

```bash
./abepke decrypt <private_key_file> <attributes_file> <cipher_file> <plaintext_file>
```

## Attributes format

Attributes need to be saved into a file with the following format:

```ini
key1=value1
key2=value2
```

This file will then be used to encrypt or decrypt data.

## Parameters

For the N parameter, the allowed values are 83, 113, 149 and 179.
The M parameter, the allowed values are 181, 151, 127, 97, 83, 89 and 67.
R and D parameters are respectively the rank of F, and E. These parameters needs to have a low value.

### Security

Here is the parameters needed for each level of security:

|Security Level| N | R | D |
|--------------|---|---|---|
|128           |83 |7  |8  |
|192           |97 |8  |8  |
|256           |113|9  |9  |

## Credits

N. Aragon, L. Bidoux, et. al. RBC Library. Version 1.3. https://rbc-lib.org. 

## Authors

This project was part of a larger research projet conducted by Killian Marty, Thomas Chourret, Leandro Rodriguez, Baptiste Rébillard, Aurélien Pouilles, Gabriel Lanoux and Sophia Salinas.

This specific encryption scheme was developped and implemented by Killian Marty.