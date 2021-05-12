#include "blockchain.h"
void _blockchain_print(blockchain_t const *blockchain);

/**
 * block_from_file_no_endn - read block from the file
 * @fptr: The file to be read from
 * Return: block  success, NULL  failure
 */
block_t *block_from_file_no_endn(FILE *fptr)
{
block_t *block;
if (fptr)
{
block = (block_t *) malloc(sizeof(block_t));
if (!block)
{
return (NULL);
}
fread((void *)&block->info.index, sizeof(block->info.index), 1, fptr);
fread((void *)&block->info.difficulty, sizeof(block->info.difficulty),
1, fptr);
fread((void *)&block->info.timestamp, sizeof(block->info.timestamp), 1, fptr);
fread((void *)&block->info.nonce, sizeof(block->info.nonce), 1, fptr);
fread((void *)&block->data.len, sizeof(block->data.len), 1, fptr);
fread(block->data.buffer, block->data.len, 1, fptr);
fread(block->hash, sizeof(block->hash), 1, fptr);
return (block);
}
return (NULL);
}
/**
 * block_from_file_endn - read block from the file
 * with swaping_endian
 * @fptr: The file to be read from
 * Return: block  success, NULL  failure
 */
block_t *block_from_file_endn(FILE *fptr)
{
block_t *block;
if (fptr)
{
block = (block_t *) malloc(sizeof(block_t));
if (block)
return (NULL);
fread((void *)&block->info.index, sizeof(block->info.index), 1, fptr);
fread((void *)&block->info.difficulty,
sizeof(block->info.difficulty), 1, fptr);
fread((void *)&block->info.timestamp, sizeof(block->info.timestamp), 1, fptr);
fread((void *)&block->info.nonce, sizeof(block->info.nonce), 1, fptr);
fread((void *)&block->data.len, sizeof(block->data.len), 1, fptr);
fread(block->data.buffer, block->data.len, 1, fptr);
fread(block->hash, sizeof(block->hash), 1, fptr);
_swap_endian(&block->hash, sizeof(block->hash));
_swap_endian(&block->data.len, sizeof(block->data.len));
_swap_endian(&block->info.index, sizeof(block->info.index));
_swap_endian(&block->info.difficulty, sizeof(block->info.difficulty));
_swap_endian(&block->info.timestamp, sizeof(block->info.timestamp));
_swap_endian(&block->info.nonce, sizeof(block->info.nonce));
return (block);
}
return (NULL);
}
/**
 * blockchain_deserialize -  load a Blockchain from the file
 * @path: the file directorie
 *
 * Return: Blockchain  success, NULL  failure
 */
blockchain_t *blockchain_deserialize(char const *path)
{
uint8_t hblk_magic[4];
uint8_t hblk_version[3];
uint8_t hblk_endian;
int32_t hblk_blocks;
block_t * (*fun_ptr)(FILE *) = &block_from_file_no_endn;
blockchain_t  *blockchain =  (blockchain_t *) malloc(sizeof(blockchain_t));
block_t *block = NULL;
int i;
FILE *fptr = fopen(path, "r+");
blockchain->chain =  llist_create(MT_SUPPORT_TRUE);
if (!fptr)
return (NULL);
fread(hblk_magic, sizeof(hblk_magic), 1, fptr);
fread(hblk_version, sizeof(hblk_version), 1, fptr);
fread(&hblk_endian, sizeof(hblk_endian), 1, fptr);
fread(&hblk_blocks, sizeof(hblk_blocks), 1, fptr);
if (strcmp((const char *)hblk_magic, (const char *)"HBLK") &&
strcmp((const char *)hblk_version, (const char *)"0.1"))
{
fclose(fptr);
return (NULL);
}
if (_get_endianness() != hblk_endian)
fun_ptr = &block_from_file_endn;
for (i = 0 ; i < hblk_blocks ; i++)
{
block = (fun_ptr)(fptr);
if (block)
{
if (llist_add_node(blockchain->chain, block,  ADD_NODE_REAR) == -1)
{
if (blockchain->chain)
blockchain_destroy(blockchain);
fclose(fptr);
return (NULL);
}
}
else
{
if (blockchain->chain)
blockchain_destroy(blockchain);
fclose(fptr);
return (NULL);
}
}
fclose(fptr);
return (blockchain);
}
