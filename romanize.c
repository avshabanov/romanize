#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "char_entries.h"

const size_t ENTRIES_HASHTABLE_CAPACITY = ENTRIES_SIZE * 1.85;

typedef struct {
  /** Bloom filter for hashtable entries */
  wint_t filter;

  CharEntry* table[ENTRIES_HASHTABLE_CAPACITY];
} LookupTable;

static inline size_t LookupTableHashCode(wint_t key) {
  return ((size_t) key) % ENTRIES_HASHTABLE_CAPACITY;
}

static inline void initLookupTable(LookupTable* t) {
  memset(t, 0, sizeof(LookupTable));

  for (size_t i = 0; i < ENTRIES_SIZE; ++i) {
    CharEntry* e = &ENTRIES[i];
    size_t hashCode = LookupTableHashCode(e->origin);
    for (size_t j = 0; j < ENTRIES_HASHTABLE_CAPACITY; ++j) {
      size_t pos = (hashCode + j) % ENTRIES_HASHTABLE_CAPACITY;
      if (t->table[pos] != NULL) {
        continue;
      }
      t->table[pos] = e;
      goto LContinue;
    }

    // shouldn't happen if capacity is big enough
    fprintf(stderr, "while inserting %c to hashtable: unable to find space for this symbol", e->origin);
    exit(EXIT_FAILURE);
  LContinue:
    // update bloom filter
    t->filter |= e->origin;
  }
}

static inline bool lookup(LookupTable* t, wint_t key, CharEntry** result) {
  // optimization: first, check the bloom filter
  wint_t f = t->filter & key;
  if (f != key) {
    // this table for sure doesn't have an entry for this key
    return false;
  }

  // hashtable lookup with collision handling code
  size_t hashCode = LookupTableHashCode(key);
  for (size_t i = 0; i < ENTRIES_HASHTABLE_CAPACITY; ++i) {
    size_t pos = (hashCode + i) % ENTRIES_HASHTABLE_CAPACITY;
    CharEntry* e = t->table[pos];
    if (e == NULL) {
      return false;
    }

    if (e->origin == key) {
      if (result != NULL) {
        *result = e;
      }
      return true;
    }
  }

  return false; // normally shouldn't happen given that hashtable capacity is generous enough
}

int main() {
  setlocale (LC_ALL, "");

  FILE *in = stdin;
  FILE *out = stdout;
  
  LookupTable lookupTable;
  initLookupTable(&lookupTable);

  for (wint_t c = fgetwc(in); c != WEOF; c = fgetwc(in)) {
    CharEntry* e;
    if (lookup(&lookupTable, c, &e)) {
      fputs(e->target, out);
      continue;
    }

    // skip unprintable characters
    if (c > 128) {
      fputwc('?', out);
      continue;
    }

    // print character as it is
    fputwc(c, out);
  }

  return EXIT_SUCCESS;
}
