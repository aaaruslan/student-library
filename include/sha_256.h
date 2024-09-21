#ifndef GRAND_TASK_SHA_256_H
#define GRAND_TASK_SHA_256_H

#include <stdint.h>
#include <string.h>

#define MAX_HASH_LENGTH 32

#define SIZE_OF_SHA_256_CHUNK 64

struct Sha_256 {
    uint8_t *hash;
    uint8_t chunk[SIZE_OF_SHA_256_CHUNK];
    uint8_t *chunk_pos;
    size_t space_left;
    size_t total_len;
    uint32_t h[8];
};


void calc_sha_256(uint8_t hash[MAX_HASH_LENGTH], const void *input, size_t len);


void sha_256_init(struct Sha_256 *sha_256, uint8_t hash[MAX_HASH_LENGTH]);


void sha_256_write(struct Sha_256 *sha_256, const void *data, size_t len);


uint8_t *sha_256_close(struct Sha_256 *sha_256);

#endif //GRAND_TASK_SHA_256_H
