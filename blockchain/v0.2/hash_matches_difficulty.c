#include "blockchain.h"
#include <stdbool.h>
/**
 * leadingZeroCalculer - calculute number of leading  zero in
 * the chain bits of hash
 * @hash: lhe hash
 * @len: The lenght de hash
 * Return: number of leadingZero  success, -1  failure
 */
uint32_t leadingZeroCalculer(uint8_t const *hash, size_t len)
{
uint8_t n, c, i, inThe;
uint32_t res = 0;
for (i = 0 ; i < len ; i++)
{
n = hash[i];
if (hash[i] == 0)
{
res += 8;
continue;
}
else
{
for (c = 0; c < 8; c++)
{
if (n & 1)
inThe = 0;
else
inThe++;
n = n >> 1;
}
res += inThe;
return (res);
}
}
return (res);
}
/**
 * hash_matches_difficulty - check if difficulty matches
 * the  hash
 * @hash: The hash
 * @difficulty: The difficulty
 * Return: 1  success, 0  failure
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
uint32_t difficulty)
{
return (leadingZeroCalculer(hash, SHA256_DIGEST_LENGTH) == difficulty ? 1 : 0);
}
