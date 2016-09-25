#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

bst_malloc_f bst_malloc = malloc;
bst_free_f bst_free = free;

int string_comparator(void * lhs, void * rhs) {
    return (int) lhs - (int) rhs;
}

void free_strings(void * key, void * value) { free(value); }

void print_strings(void * key, void * value) { 
    printf("%d: %s\n", (int) key, value);
}

int main() {
    struct BstTree tree;
    const char * lines[] = {
        "one", "two", "three", "four", "five", "six", "seven", "fourty two"
    };
    int i;
    bst_init(&tree, string_comparator);
    for (i = 0; i < sizeof(lines) / sizeof(const char *); ++i) {
        bst_set(&tree, (void *) strlen(lines[i]), (void *) lines[i]);
    }
    bst_traverse(&tree, print_strings);
    bst_destroy(&tree);
    return 0;
}
