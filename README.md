# Rank-Based ABE KEM

## Introduction

This algorithm is based on RolloI and add a layer of ABE using cipher text policy with bloom filters.
In this implementation, the RBC-Lib is used.

## Installation

Clone this repo and run:

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
./abekem keygen <public_key_file> <private_key_file>
```

To generate the DEM Key (currently an AES-512 key) and cipher it:

```bash
./abekem encaps <public_key_file> <cipher_file>
```

To decode the cipher and recover the DEM Key:

```bash
./abekeme decaps <private_key_file> <cipher_file>
```