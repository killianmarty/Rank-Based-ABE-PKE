#ifndef ATTR_H
#define ATTR_H

#define ATTRIBUTE_KEY_SIZE 32
#define ATTRIBUTE_VALUE_SIZE 32
#define ATTRIBUTE_STRING_SIZE (ATTRIBUTE_KEY_SIZE + ATTRIBUTE_VALUE_SIZE + 1)

#include <stdio.h>

typedef struct {
    char key[ATTRIBUTE_KEY_SIZE];
    char value[ATTRIBUTE_VALUE_SIZE];
} Attribute;

void attribute_to_string(Attribute *att, char *str);

#endif