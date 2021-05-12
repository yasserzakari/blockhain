#include "hblk_crypto.h"


int ec_save(EC_KEY *key, char const *folder)
{
	char file[512];
	FILE *f;
	struct stat st;

	if (!key || !folder)
		return 0;
	if (stat(folder, &st) == -1)
	{
		if (mkdir(folder, 0700) == -1)
			return 0;
	}
	sprintf(file, "%s/%s", folder, PRI_FILENAME);
	f = fopen(file, "w");
	if (!f)
		return 0;
	if (!PEM_write_ECPrivateKey(f, key, NULL, NULL, 0, NULL, NULL))
		return 0;
	fclose(f);
	sprintf(file, "%s/%s", folder, PUB_FILENAME);
	f = fopen(file, "w");
	if (!f)
		return 0;
	if (!PEM_write_EC_PUBKEY(f, key))
		return 0;
	fclose(f);
	return 1;
}
