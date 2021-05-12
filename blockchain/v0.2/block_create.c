#include "blockchain.h"
/**
 * block_create - create a block and initialises it
 *@prev: previous  block
 *@data: data to be stored in the block
 *@data_len: length of data
 * Return: a new block structure or NULL
 */
block_t *block_create(block_t const *prev, int8_t const *data,
uint32_t data_len)
{
uint32_t i;
time_t sec = (time_t)2;
block_t *block = (block_t *) malloc(sizeof(block_t));
if (!prev || !data)
return (NULL);
block->info.index = prev->info.index + 1;
block->info.difficulty = 0;
block->info.nonce = 0;
block->info.timestamp = time(&sec);
memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
memcpy(block->data.buffer, data, BLOCKCHAIN_DATA_MAX);
if (data_len > (uint32_t)BLOCKCHAIN_DATA_MAX)
block->data.len = BLOCKCHAIN_DATA_MAX;
else
block->data.len = data_len;
for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
block->hash[i] = 0;
return (block);
}
