#include "blockchain.h"
/**
 * block_destroy - destroy a block
 *@block: the block to be destroy
 */
void block_destroy(block_t *block)
{
free(block);
}
