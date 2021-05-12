#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder)
{
	EC_KEY *key = NULL;
	char file[512] = {0};
	FILE *f;
	struct stat st;

	if (!folder)
		return NULL;
	if (stat(folder, &st) == -1)
		return NULL;
	sprintf(file, "./%s/%s", folder, PUB_FILENAME);
	f = fopen(file, "r");
	if (!f)
		return NULL;
	if (!PEM_read_EC_PUBKEY(f, &key, NULL, NULL))
		return NULL;
	fclose(f);
	sprintf(file, "./%s/%s", folder, PRI_FILENAME);
	f = fopen(file, "r");
	if (!f)
		return NULL;
	if (!PEM_read_ECPrivateKey(f, &key, NULL, NULL))
		return NULL;
	fclose(f);
	return key;
}


