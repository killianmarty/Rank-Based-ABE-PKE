#!/bin/bash

# Ensure script runs from its own directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# Variables
ZIP_URL="https://rbc-lib.org/doc/rbc-1.3.zip"
TMP_DIR=$(mktemp -d)
FILE_TO_REPLACE="config.yml"
PYTHON_SCRIPT="rbc-lib.py"
BASE64_CONTENT="IyoqKioqKioqKioqKioqKioqKioqKioqKiojCiMqKiogUkJDIGNvbmZpZ3VyYXRpb24gKioqIwojKioqKioqKioqKioqKioqKioqKioqKioqKiMKCnJiY19jb3JlX2xheWVyX2ltcGxlbTogYXZ4CgpyYmNfYnVpbGRfcGFyYW1ldGVyczogWwogIHsibmFtZSI6InJxYyIsICAgICAgICJzZWNfbHZsIjoxMjgsICAgIm0iOjEyNywgICAibiI6MTEzfSwKICB7Im5hbWUiOiJycWMiLCAgICAgICAic2VjX2x2bCI6MTkyLCAgICJtIjoxNTEsICAgIm4iOjE0OX0sCiAgeyJuYW1lIjoicnFjIiwgICAgICAgInNlY19sdmwiOjI1NiwgICAibSI6MTgxLCAgICJuIjoxNzl9LAoKICB7Im5hbWUiOiJyb2xsb0kiLCAgICAic2VjX2x2bCI6MjU2LCAgICJtIjoxODEsICAgICJuIjoxNzl9LAogIHsibmFtZSI6InJvbGxvSUkiLCAgICAic2VjX2x2bCI6MTI4LCAgICJtIjo2NywgICAgIm4iOjgzfQoKXQoKcmJjX2NvbXBpbGVfZXhhbXBsZTogVHJ1ZQpyYmNfY29tcGlsZV91bml0X3Rlc3Q6IFRydWUKcmJjX2NvbXBpbGVfY29uc3RhbnRfdGltZV90ZXN0OiBGYWxzZQpyYmNfY29tcGlsZV9rYXQ6IEZhbHNlCgpyYmNfY29tcGlsZV9iZW5jaG1hcms6IEZhbHNlCnJiY19wYWNrYWdlX25pc3Q6IEZhbHNlCg=="


echo "Downloading library..."
curl -L -o "$TMP_DIR/archive.zip" "$ZIP_URL"

echo "Extracting library..."
unzip -q "$TMP_DIR/archive.zip" -d "$TMP_DIR/unzipped"

TARGET_FILE="$TMP_DIR/unzipped/$FILE_TO_REPLACE"
if [ -f "$TARGET_FILE" ]; then
    echo "Configuring library..."
    echo "$BASE64_CONTENT" | base64 -d > "$TARGET_FILE"
else
    echo "Error: $FILE_TO_REPLACE not found."
    exit 1
fi

# Create a symbolic link to the Python binary
TMP_BIN="$TMP_DIR/tmpbin"
mkdir -p "$TMP_BIN"
ln -s "$(which python3)" "$TMP_BIN/python"

cd "$TMP_DIR/unzipped" || exit 1
echo "Running installation..."
PATH="$TMP_BIN:$PATH" python3 "$PYTHON_SCRIPT"

echo "Copying installation files..."
cp "$TMP_DIR/unzipped/bin/librbc.a" "$TMP_DIR/unzipped/bin/librbc-nist.a" "$SCRIPT_DIR/lib/rbc_lib/"

echo "Cleaning up..."
rm -rf "$TMP_DIR"

echo "Sucessfully installed."
