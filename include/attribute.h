#ifndef ATTR_H
#define ATTR_H

#define ATTRIBUTE_KEY_SIZE 32
#define ATTRIBUTE_VALUE_SIZE 32
#define ATTRIBUTE_STRING_SIZE (ATTRIBUTE_KEY_SIZE + ATTRIBUTE_VALUE_SIZE + 1)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char key[ATTRIBUTE_KEY_SIZE];
    char value[ATTRIBUTE_VALUE_SIZE];
} Attribute;

typedef struct {
    int count;
    int size;
    Attribute *attributes;
} AttributeList;

void attribute_to_string(Attribute *att, char *str);

void attribute_list_init(AttributeList *list, int size);
void attribute_list_add(AttributeList *list, const char *key, const char *value);
void attribute_list_free(AttributeList *list);
void attribute_list_print(AttributeList *list);


#endif