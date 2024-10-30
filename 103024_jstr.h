#ifndef JSTR_H
#define JSTR_H

struct String {
    uint64_t length;
    char* contents;
};

typedef struct String String;


String new_String(char* init_contents);
String plus(String s1, String s2);
String join(String strs[], int count, String delimiter);

#endif
