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

## Parameters

For the N parameter, the allowed values are 83, 113, 149 and 179.
The M parameter is constant in this implementation (M=181)
R and D parameters are respectively the rank of F, and E. These parameters needs to have a low value.

### Security

Here is the parameters needed for each level of security:

|Security Level| N | R | D |
|--------------|---|---|---|
|128           |83 |7  |8  |
|192           |97 |8  |8  |
|256           |113|9  |9  |