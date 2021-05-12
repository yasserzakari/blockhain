#include "blockchain.h"
/**
 *blockchain_destroy - destroy a blockchain
 *@blockchain: the blockchain to be destroy
 */
void blockchain_destroy(blockchain_t *blockchain)
{
if (blockchain)
{
llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
free(blockchain);
}
}
