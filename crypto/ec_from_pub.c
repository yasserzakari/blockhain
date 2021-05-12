#include "hblk_crypto.h"


EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_POINT *pkey;
	EC_GROUP *group;

	if (!pub)
		return NULL;
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return NULL;
	group = EC_GROUP_new_by_curve_name(EC_CURVE);
	if (!group)
		return NULL;
	pkey = EC_POINT_new(group);
	if (!pkey)
	{
		EC_GROUP_free(group);
		return NULL;
	}
	if (!EC_POINT_oct2point(group, pkey, pub, EC_PUB_LEN, NULL))
		return NULL;
	if (!EC_KEY_set_public_key(key, pkey))
	{
		EC_POINT_free(pkey);
		EC_GROUP_free(group);
		return NULL;
	}
	EC_POINT_free(pkey);
	EC_GROUP_free(group);
	return key;
}
