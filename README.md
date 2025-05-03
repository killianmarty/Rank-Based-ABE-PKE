# Rank-Based ABE PKE

## Introduction

This scheme is based on Rollo-II and add a layer of ABE using cipher text policy with bloom filters.

## Installation

Warning, you will first need to install rbc_lib. Just run:

```bash
make install_rbc
```

Or if you want to edit the rbclib's configuration, edit `rbc_config.yml` before.

Then just run:

```bash
make
```

You can also run unit tests with:

```bash
make test
```

Moreover, we can run benchmarks with the following command:

```bash
sudo perf stat ./benchmark.sh [keygen | encrypt | decrypt] <nb_iter>
```

## Usage

To generate the public and private keys:

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

## Scheme

Because this scheme is based on Rollo-II, the principle is very similar.

### Rollo-II scheme

#### Keygen

```
Inputs : None

F = generate_support_fixed_dimension(R)
x, y = generate_pair_from_support(F)
h = x⁻¹ * y

Output pk=(h), sk=(x,y,F)
```

#### Encrypt

```
Inputs : pk, plaintext

E = generate_support_fixed_dimension(D)
e₁, e₂ = generate_pair_from_support(E)
cipher = e₁ + e₂ * pk.h

encrypted = plaintext ⊕ hash(E)

Output msg = (encrypted, cipher)
```

#### Decrypt

```
Inputs : sk, msg

xc = sk.x × cipher
E = RSR(xc, F)

decrypted = msg.encrypted ⊕ hash(E)

Output plaintext = (decrypted)
```

### Rank-Based ABE PKE

#### Auxiliary functions

`BF(Attributes)`: Computes Bloom filter of Attributes.

`H(BF)`: Hash a Bloom Filter into a $F_{q^m}^n$ element.

`RecoverBF(msg.BF_keys, Attributes)`: Create a Bloom Filter with the only attributes of the user that are needed to decrypt the cipher.

#### Keygen

The keygen is the same as Rollo-II.

#### Encrypt

```
Inputs : pk, Attributes, plaintext

E = generate_support_fixed_dimension(D)
e₁, e₂ = generate_pair_from_support(E)
cipher = e₁ + e₂ * pk.h

BF_att = BF(Attributes)
BF_keys = BF(Attributes.keys())

s = H(BF_att)
cipher' = cipher × s

encrypted = plaintext ⊕ hash(E)

Output msg = (encrypted, cipher', BF_keys)
```

#### Decrypt

```
Inputs : sk, Attributes, msg

BF_Attr = RecoverBF(msg.BF_keys, Attributes)
    
s = H(BF_Attr)
cipher = cipher' × s⁻¹
xc = sk.x × cipher
E = RSR(xc, F)

decrypted = msg.encrypted ⊕ hash(E)

Output plaintext=(decrypted)
```

## Parameters

For the N parameter, the allowed values are 83, 113, 149, 179, 189, 193 and 211.
The M parameter, the allowed values are 181, 151, 127, 97, 89, 83 and 67.
R and D parameters are respectively the rank of F, and E. These parameters needs to have a low value.

### Security

Here are the parameters needed for each level of security (at the Rollo-II layer) and the decoding failure rate associated:

|Security Level| N | M | R | D | |    DFR     |
|--------------|---|---|---|---|-|------------|
|128           |189|83 |7  |8  | |$`2^{-134}`$|
|192           |193|97 |8  |8  | |$`2^{-130}`$|
|256           |211|97 |8  |9  | |$`2^{-136}`$|

**Warning**: As the ABE layer uses Bloom Filters to check the attributes, there is a risk of false positives. This risk reduces the security of the ABE layer only because the security of the RolloII layer is not dependant of the ABE layer.

The risk of false positive of the bloom filter is given by :

$`p = \left(1 - e^{-\frac{k}{m / n}}\right)^k`$

Where:
- `k` is the number of hash functions,
- `n` is the number of elements in the set,
- `m` is the size of the Bloom filter in bits.

So, it is important to choose parameters that reduces the false positive probability. But be careful: increasing `m` and `k` increases the cipher size.

### Performance

Theses benchmarks were performed with the following configuration on `1000` iterations:
- CPU : AMD Ryzen 7 8845HS
- RAM : 32 Go LPDDR5X-6 400MT/s
- Architecture : 64 bits
- Operating system : Debian 12

### Standard version (x64)

The values are in millions of CPU cycles.

| Security Level | Keygen  | Encrypt | Decrypt |
|----------------|---------|---------|---------|
| 128            | 182.2   | 16.2    | 194.9   |
| 192            | 212.7   | 18.1    | 227.7   |
| 256            | 254.4   | 19.5    | 269.0   |

### AVX optimized version

The values are in millions of CPU cycles.

| Security Level | Keygen  | Encrypt | Decrypt |
|----------------|---------|---------|---------|
| 128            | 8.1     | 7.8     | 12.8    |
| 192            | 7.3     | 8.1     | 12.3    |
| 256            | 7.9     | 7.7     | 13.8    |

## Credits

N. Aragon, L. Bidoux, et. al. RBC Library. Version 1.3. https://rbc-lib.org.

Aguilar Melchor, C., Aragon, N., Bardet, M., Bettaieb, S., Bidoux, L., Blazy, O., Deneuville, J.-C., Gaborit, P., Hauteville, A., Otmani, A., Ruatta, O., Tillich, J.-P., & Zémor, G. (2020, April 21). ROLLO – Rank-Ouroboros, LAKE & LOCKER. https://pqc-rollo.org.

## Authors

This project was part of a larger research projet conducted by Killian Marty, Thomas Chourret, Leandro Rodriguez, Baptiste Rébillard, Aurélien Pouilles, Gabriel Lanoux and Sofia Salinas.

This specific encryption scheme was developped and implemented by Killian Marty.