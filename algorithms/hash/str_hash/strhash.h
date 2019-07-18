#ifndef STRHASH_H
#define STRHASH_H

#include <stdio.h>
#include <assert.h>

int bkdr_hash(void *);

int ap_hash(void *);

int js_hash(void *);

int rs_hash(void *);

int sdbm_hash(void *);

int pjw_hash(void *);

int elf_hash(void *);

int djb_hash(void *);

int dek_hash(void *, size_t);

int bp_hash(void *, size_t);

int fnv_hash(void *);

int java_hash(void *);

#endif // !STRHASH_H
