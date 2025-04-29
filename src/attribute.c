#include "attribute.h"

void attribute_to_string(Attribute *att, char *str){
    sprintf(str, "%s=%s", att->key, att->value);
}
