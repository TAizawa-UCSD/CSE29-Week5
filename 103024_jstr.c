#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "103024_jstr.h"


String new_String(char* init_contents) {
    uint64_t size = strlen(init_contents);
    char* contents = malloc(size + 1);
    strcpy(contents, init_contents);
    String r = { size, contents };
    return r;
}

// This plus is *just* the heap-allocating version now
String plus(String s1, String s2) {
    uint64_t new_size = s1.length + s2.length + 1;
    char* new_contents = calloc(new_size, sizeof(char));
    strncpy(new_contents, s1.contents, s1.length);
    strncpy(new_contents + s1.length, s2.contents, s2.length);
    new_contents[new_size - 1] = 0;
    String r = { new_size - 1, new_contents };
    return r;
}

String join(String strs[], int count, String delimiter) {
    int total_length = 0;
    for(int i = 0; i < count; i += 1) {
        total_length += strs[i].length;
        if(i < count - 1) { total_length += delimiter.length; }
    }
    char* new_contents = malloc(total_length + 1);
    int index = 0;
    for(int i = 0; i < count; i += 1) {
        strcpy(new_contents + index, strs[i].contents);
        if(i < count - 1) {
            strcpy(new_contents + index + strs[i].length, delimiter.contents);
        }
        index += strs[i].length + delimiter.length;
    }
    new_contents[total_length - 1] = 0;
    String r = { total_length, new_contents };
    return r;
}
