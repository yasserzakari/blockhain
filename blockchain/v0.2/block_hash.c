#include "blockchain.h"
/**
 * block_hash - to hash a passed block
 *@block: block to be hashed
 *@hash_buf: where stock hashed block
 * Return: hashed block or NULL
 */
uint8_t *block_hash(block_t const *block,
uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
size_t length = block->data.len + sizeof(block->info);
if (block)
if (sha256((int8_t const *)block, length, hash_buf))
return (hash_buf);
return (NULL);
}
