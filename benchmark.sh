#!/bin/bash

n=${2:-1000}

if [[ "$1" == "keygen" ]]; then
    for ((i=1; i<=n; i++)); do
        eval "./abepke keygen /dev/null /dev/null"
    done
elif [[ "$1" == "encrypt" ]]; then
    eval "./abepke keygen /tmp/pubkey /tmp/privkey"
    echo -e "attr1=val1\nattr2=val2\nattr3=val3\nattr4=val4\nattr5=val5\nattr6=val6\nattr7=val7\nattr8=val8\nattr9=val9\nattr10=val10" > /tmp/attrs
    echo "plaintext" > /tmp/plaintext
    for ((i=1; i<=n; i++)); do
        eval "./abepke encrypt /tmp/pubkey /tmp/attrs /tmp/plaintext /dev/null"
    done
    rm /tmp/plaintext
    rm /tmp/attrs
    rm /tmp/pubkey
    rm /tmp/privkey
elif [[ "$1" == "decrypt" ]]; then
    eval "./abepke keygen /tmp/pubkey /tmp/privkey"
    echo -e "attr1=val1\nattr2=val2\nattr3=val3\nattr4=val4\nattr5=val5\nattr6=val6\nattr7=val7\nattr8=val8\nattr9=val9\nattr10=val10" > /tmp/attrs
    echo "plaintext" > /tmp/plaintext
    eval "./abepke encrypt /tmp/pubkey /tmp/attrs /tmp/plaintext /tmp/cipher"
    for ((i=1; i<=n; i++)); do
        eval "./abepke decrypt /tmp/privkey /tmp/attrs /tmp/cipher /dev/null"
    done
    rm /tmp/cipher
    rm /tmp/plaintext
    rm /tmp/attrs
    rm /tmp/pubkey
    rm /tmp/privkey
else
    echo "Invalid parameter. Use 'keygen', 'encrypt' or 'decrypt' as the first argument."
    exit 1
fi