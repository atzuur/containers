#include <stdio.h>
#include <string.h>
#include "dict.h"

int main (int argc, char *argv[]) {
    struct dict *d = (struct dict*)malloc(sizeof(struct dict));
    dict_init(d, (char*[]){"key1", "key2"},(char*[]){"val1", "val2"}, 2);
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) for (size_t i = 0; i < d->count; i++) printf("%p %s %p %s\n", d->keys[i], d->keys[i], d->vals[i], d->vals[i]);
    if ((strcmp(d->keys[0], "key1") == 0) && (strcmp(d->keys[1], "key2") == 0) && (strcmp(d->vals[0], "val1") == 0) && (strcmp(d->vals[1], "val2") == 0)) {
        printf("dict_init() passed\n");
    } else {
        printf("dict_init() failed\n");
        return 0;
    }
    dict_add(d, "key3", "val3");
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) for (size_t i = 0; i < d->count; i++) printf("%p %s %p %s\n", d->keys[i], d->keys[i], d->vals[i], d->vals[i]);
    if ((strcmp(d->keys[0], "key1") == 0) && (strcmp(d->keys[1], "key2") == 0) && (strcmp(d->keys[2], "key3") == 0) && (strcmp(d->vals[0], "val1") == 0) && (strcmp(d->vals[1], "val2") == 0) && (strcmp(d->vals[2], "val3") == 0)) {
        printf("dict_add() passed\n");
    } else {
        printf("dict_add() failed\n");
        return 0;
    }
    dict_rem(d, 1);
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) for (size_t i = 0; i < d->count; i++) printf("%p %s %p %s\n", d->keys[i], d->keys[i], d->vals[i], d->vals[i]);
    if ((strcmp(d->keys[0], "key1") == 0) && (strcmp(d->keys[1], "key3") == 0) && (strcmp(d->vals[0], "val1") == 0) && (strcmp(d->vals[1], "val3") == 0)) {
        printf("dict_rem() passed\n");
    } else {
        printf("dict_rem() failed\n");
        return 0;
    }
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) printf("0: %p %s %p %s\n", d->keys[0], d->keys[0], d->vals[0], d->vals[0]);
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) printf("1: %p %s %p %s  <--- here\n", d->keys[1], d->keys[1], d->vals[1], d->vals[1]);
    int querytest = dict_query(d, "key3", true);
    if (querytest == 1) {
        if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) printf("output: 1\n");
        printf("dict_query() passed\n");
    } else {
        if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) printf("output: %d\n", querytest);
        printf("dict_quesry() failed\n");
        return 0;
    }
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) for (size_t i = 0; i < d->count; i++) printf("%p %s %p %s%s\n", d->keys[i], d->keys[i], d->vals[i], d->vals[i], d->dups[i] ? " dup" : "");
    if ((d->dups[0] == false) && (d->dups[1] == false) && (d->dups[2] == false)) {
        printf("dict_finddups() 1 passed\n");
    } else {
        printf("dict_finddups() 1 failed\n");
        return 0;
    }
    dict_add(d, "key3", "val3");
    if ((argc == 2) && (strcmp(argv[1], "debug") == 0)) for (size_t i = 0; i < d->count; i++) printf("%p %s %p %s%s\n", d->keys[i], d->keys[i], d->vals[i], d->vals[i], d->dups[i] ? " dup" : "");
    if ((d->dups[0] == false) && (d->dups[1] == true) && (d->dups[2] == true)) {
        printf("dict_finddups() 2 passed\n");
    } else {
        printf("dict_finddups() 2 failed\n");
        return 0;
    }

    printf("All tests passed\n");
    dict_free(d);
    free(d);
    return 0;
}