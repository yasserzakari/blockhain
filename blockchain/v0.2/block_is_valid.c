#include "blockchain.h"
/**
 * is_genesis - checck if the block is genesis
 * @block: The file to be read from
 * Return: 0  success, -1  failure
 */
int is_genesis(block_t const *block)
{
blockchain_t *blockchain = blockchain_create();
if (!blockchain)
return (-1);
if (memcmp(block, llist_get_head(blockchain->chain), sizeof(*block)) != 0)
{
blockchain_destroy(blockchain);
return (-1);
}
blockchain_destroy(blockchain);
return (0);
}
/**
 * verify_blocks - verify the validity of a block
 * @block: The file to be read from
 * @prev_block: The file to be read from
 * Return: 0  success, -1  failure
 */
int verify_blocks(block_t const *block, block_t const *prev_block)
{
uint8_t block_sha[SHA256_DIGEST_LENGTH];
uint8_t prev_sha[SHA256_DIGEST_LENGTH];
if (prev_block->info.index != block->info.index - 1)
return (-1);
if (is_genesis(prev_block) == -1)
if (!block_hash(prev_block, prev_sha) ||
memcmp(prev_block->hash, prev_sha, SHA256_DIGEST_LENGTH))
return (-1);
if (!block_hash(block, block_sha) ||
memcmp(block->hash, block_sha, SHA256_DIGEST_LENGTH) ||
memcmp(block->info.prev_hash, prev_block->hash, SHA256_DIGEST_LENGTH))
return (-1);
if (block->data.len > BLOCKCHAIN_DATA_MAX)
return (-1);
return (0);
}
/**
 * block_is_valid - check if the block is valid
 * @block: The file to be read from
 * @prev_block: The file to be read from
 * Return: 0  success, -1  failure
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
if (!block)
return (-1);
if (!hash_matches_difficulty(block->hash,
block->info.difficulty))
return (-1);
if (!prev_block && !block->info.index)
return (is_genesis(block));
if (!hash_matches_difficulty(prev_block->hash,
prev_block->info.difficulty))
return (-1);
return (verify_blocks(block, prev_block));
}
