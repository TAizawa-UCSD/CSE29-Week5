#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct String {
    uint64_t length;    // should always equal strlen(contents)
    char* contents;     // should always have allocated space of length + 1, including null terminator
};

typedef struct String String;

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
    String s = new_String("");
    for(int i = 0; i < count; i += 1) {
        s = plus(s, strs[i]);
        if(i < count - 1) {
            s = plus(s, delimiter);
        }
    }
    return s;
}

int main() {
    String apple = new_String("apple");
    String banana = new_String("banana");
    String strawberry = new_String("strawberry");
    String fruit[] = { apple, banana, strawberry };

    String comma = new_String(", ");
    String fruitlist = join(fruit, 3, comma);
    printf("%s\n", fruitlist.contents);
}




String joinfree(String strs[], int count, String delimiter) {
    String s = new_String("");
    for(int i = 0; i < count; i += 1) {
        char* before_plus = s.contents;
        s = plus(s, strs[i]);
        free(before_plus);
        if(i < count - 1) {
            char* before_plus = s.contents;
            s = plus(s, delimiter);
            free(before_plus);
        }
    }
    return s;
}

String join_nogarbage(String strs[], int count, String delimiter) {
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
