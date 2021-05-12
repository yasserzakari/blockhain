#include "hblk_crypto.h"


uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX sha_ctx;
	
	if(digest && s)
	{
	  		
	SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx,s,len);
	SHA256_Final(digest,&sha_ctx);
	
	return digest;	
	}

	return NULL;	
}

