#include "attribute.h"

void attribute_to_string(Attribute *att, char *str){
    sprintf(str, "%s=%s", att->key, att->value);
}

void attribute_list_init(AttributeList *list, int size){
    list->count = 0;
    list->size = size;
    list->attributes = calloc(size, sizeof(Attribute));
}

void attribute_list_add(AttributeList *list, const char *key, const char *value){
    if(list->count >= list->size){
        printf("Attribute list is full\n");
        return;
    }

    strncpy(list->attributes[list->count].key, key, ATTRIBUTE_KEY_SIZE-1);
    strncpy(list->attributes[list->count].value, value, ATTRIBUTE_VALUE_SIZE-1);
    list->attributes[list->count].key[ATTRIBUTE_KEY_SIZE-1] = '\0';
    list->attributes[list->count].value[ATTRIBUTE_VALUE_SIZE-1] = '\0';
    list->count++;
}

void attribute_list_free(AttributeList *list){
    free(list->attributes);
    list->attributes = NULL;
    list->count = 0;
    list->size = 0;
}

void attribute_list_print(AttributeList *list){
    for(int i = 0; i < list->count; i++){
        printf("%s=%s\n", list->attributes[i].key, list->attributes[i].value);
    }
}