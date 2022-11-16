#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct dict {
    size_t count; // starts at 1, equals to highest index + 1
    bool *dups;
    char **keys;
    char **vals;
} dict;

void dict_init (dict *d, char *keys[], char *vals[], size_t count);
bool dict_exist(dict *d, char korv[], bool key); // if key is false, vals is searched instead
void dict_add (dict *d, char key[], char val[]);
void dict_rem (dict *d, size_t l); // l is the array index
void dict_free(dict *d);
size_t dict_query (dict *d, char a[], bool key); // returns the array index
void dict_finddups(dict *d); // only finds, only called by init, add and rem.
// it is C, not an object-oriented language. Write your own iterator 