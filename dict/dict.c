#include "dict.h"

void dict_init (dict *d, char *keys[], char *vals[], size_t count) {
    d->count = count;
    d->keys = (char**)malloc(count * sizeof(char*));
    d->vals = (char**)malloc(count * sizeof(char*));
    for (size_t i = 0; i < count; i++) {
        d->keys[i] = (char*)malloc((strlen(keys[i])+1) * sizeof(char));
        strcpy(d->keys[i], keys[i]);
        d->vals[i] = (char*)malloc((strlen(vals[i])+1) * sizeof(char));
        strcpy(d->vals[i], vals[i]);
    }
    d->dups = (bool*)malloc(d->count * sizeof(bool));
    dict_finddups(d);
}

void dict_add (dict *d, char key[], char val[]) {
    d->count++;
    d->keys = realloc(d->keys, d->count * sizeof(char*));
    d->vals = realloc(d->vals, d->count * sizeof(char*));
    d->keys[d->count-1] = (char*)malloc((strlen(key)+1)*sizeof(char));
    strcpy(d->keys[d->count-1], key);
    d->vals[d->count-1] = (char*)malloc((strlen(val)+1)*sizeof(char));
    strcpy(d->vals[d->count-1], val);
    d->dups = (bool*)realloc(d->dups, d->count * sizeof(bool));
    dict_finddups(d);
}

void dict_rem (dict *d, size_t l) {
    d->count--;
    for (size_t i = l+1; i <= d->count; i++) {
        d->keys[i-1] = realloc(d->keys[i-1], (strlen(d->keys[i])+1) * sizeof(char));
        strcpy(d->keys[i-1],d->keys[i]);
        d->vals[i-1] = realloc(d->vals[i-1], (strlen(d->vals[i])+1) * sizeof(char));
        strcpy(d->vals[i-1],d->vals[i]);
    }
    free(d->keys[d->count]);
    free(d->vals[d->count]);
    d->keys = realloc(d->keys, d->count * sizeof(char*));
    d->vals = realloc(d->vals, d->count * sizeof(char*));
    d->dups = (bool*)realloc(d->dups, d->count * sizeof(bool));
    dict_finddups(d);
}

void dict_finddups(dict *d) {
    for (size_t i = 0; i < d->count; i++) {
        d->dups[i] = false;
    }

    for (size_t i = 0; i < d->count; i++) {
        for (size_t j = i+1; j < d->count  ; j++) {
            if (strcmp(d->keys[i], d->keys[j]) == 0) {
                d->dups[i] = true;
                d->dups[j] = true;
            }
        }

    }
}


bool dict_exist(dict *d, char *korv, bool key) {
    if (key) {
        for (size_t i = 0; i < d->count; i++) {
            if (strcmp(d->keys[i], korv) == 0) return true;
        }
    } else {
        for (size_t i = 0; i < d->count; i++) {
            if (strcmp(d->vals[i], korv) == 0) return true;
        }
    }
    return false;
}

size_t dict_query (dict *d, char a[], bool key) {
    if (key) {
        for (size_t i = 0; i < d->count; i++) {
            if (strcmp(d->keys[i], a) == 0) return i;
        }
    } else {
        for (size_t i = 0; i < d->count; i++) {
            if (strcmp(d->vals[i], a) == 0) return i;
        }
    }
    return 0;
}

void dict_free(dict *d) {
    for (size_t i = 0; i < d->count; i++) {
        free(d->keys[i]);
        free(d->vals[i]);
    }
    free(d->keys);
    free(d->vals);
    free(d->dups);
}