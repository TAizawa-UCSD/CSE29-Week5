#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "./jstr.h"

struct List {
    uint32_t size;
    uint32_t capacity;
    String* contents;        //Let's make a list of String!
};
typedef struct List List;

List new_List() {
    List a = { 0, 10, calloc(10, sizeof(String)) };
    return a;
}

void expandCapacity(List* a) {
    uint32_t new_cap = a->capacity * 2;
    String* new_ptr = realloc(a->contents, new_cap * sizeof(String));
    a->capacity = new_cap;
    a->contents = new_ptr;
}

// if a is not a pointer, a is a copy, so the changes won't be reflected in the caller.
void append1(List *a, String value) {
    if(a->size + 1 == a->capacity) {
        expandCapacity(a);
    }
    a->contents[a->size] = value;
    a->size += 1;
}

String to_string(List a) {
    String joined = join(a.contents, a.size, new_String(", "));
    String bracket = new_String("[");
    String cbracket = new_String("]");
    String withbrack = plus(bracket, joined);
    String ret = plus(withbrack, cbracket);
    free(bracket.contents);
    free(cbracket.contents);
    free(joined.contents);
    free(withbrack.contents);
    return ret;
}

int main() {
    List a = new_List();
    append1(&a, new_String("apple"));
    append1(&a, new_String("banana"));
    append1(&a, new_String("cranberry"));
    append1(&a, new_String("doughnut"));

    String astr = to_string(a);
    printf("%s\n", astr.contents);

    free(a.contents);
    for(int i = 0; i < a.size; i += 1) {
        free(a.contents[i].contents);
    }
    free(astr.contents);
}
