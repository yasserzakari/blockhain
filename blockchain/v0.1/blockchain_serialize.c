#include "blockchain.h"

/**
 * block_to_file - write block fileds into passed file
 * @blockPtr: pointer to the block
 * @no: index of the block unsed in my  case
 * @file: The file to be stored into
 * Return: 0  success, -1  failure
 */
int block_to_file(llist_node_t blockPtr, unsigned int no, void *file)
{
block_t *block = blockPtr;
FILE *fptr;
no = -1;
if (file)
{
fptr = (FILE *)file;
fwrite((void *)&block->info.index, sizeof(block->info.index), 1, fptr);
fwrite((void *)&block->info.difficulty, sizeof(block->info.difficulty),
1, fptr);
fwrite((void *)&block->info.timestamp, sizeof(block->info.timestamp), 1, fptr);
fwrite((void *)&block->info.nonce, sizeof(block->info.nonce), 1, fptr);
fwrite((void *)&block->data.len, sizeof(block->data.len), 1, fptr);
fwrite(block->data.buffer, block->data.len, 1, fptr);
fwrite(block->hash, sizeof(block->hash), 1, fptr);
return (0);
}
return (no);
}
/**
 * blockchain_serialize -  serializes a Blockchain and save it into file
 * @blockchain: blockchain pointer
 * @path: the file directorie
 *
 * Return: 0  success, -1  failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
uint8_t hblk_magic[4];
uint8_t hblk_version[3];
uint8_t hblk_endian;
int32_t hblk_blocks;
FILE *fptr = fopen(path, "w");
if (!fptr)
return (-1);
if (blockchain && path)
{
hblk_blocks = llist_size(blockchain->chain);
if (hblk_blocks == -1)
return (-1);
memcpy(hblk_magic, "HBLK", 4);
memcpy(hblk_version, "0.1", 3);
hblk_endian = _get_endianness();
fwrite(&hblk_magic, sizeof(hblk_magic), 1, fptr);
fwrite(&hblk_version, sizeof(hblk_version), 1, fptr);
fwrite(&hblk_endian, sizeof(hblk_endian), 1, fptr);
fwrite(&hblk_blocks, sizeof(hblk_blocks), 1, fptr);
if (llist_for_each(blockchain->chain, block_to_file, fptr))
{
fclose(fptr);
return (0);
}
}
fclose(fptr);
return (-1);
}
