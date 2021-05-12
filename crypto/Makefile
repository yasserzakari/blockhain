CFLAGS = -Wall -Wextra -Werror -pedantic -I.
HEADERS = hblk_crypto.h
CC = gcc
sha256.o:  sha256.c $(HEADERS)
	${CC} ${CFLAGS}  sha256.c -c -lssl -lcrypto
ec_create.o : ec_create.c $(HEADERS)
	${CC} ${CFLAGS}  ec_create.c -c  -lssl -lcrypto
ec_to_pub.o: ec_to_pub.c $(HEADERS)
	${CC} ${CFLAGS}  ec_to_pub.c -c -lssl -lcrypto
ec_from_pub.o: ec_from_pub.c $(HEADERS)
	${CC} ${CFLAGS}  ec_from_pub.c -c -lssl -lcrypto
ec_save.o: ec_save.c $(HEADERS)
	${CC} ${CFLAGS}  ec_save.c -c -lssl -lcrypto
ec_load.o: ec_load.c $(HEADERS)
	${CC} ${CFLAGS}  ec_load.c -c -lssl -lcrypto
ec_sign.o: sha256.c $(HEADERS)
	${CC} ${CFLAGS}  ec_sign.c -c -lssl -lcrypto
ec_verify.o: ec_verify.c $(HEADERS)
	${CC} ${CFLAGS} ec_verify.c -c -lssl -lcrypto
libhblk_crypto.a: sha256.o ec_create.o ec_to_pub.o ec_from_pub.o ec_save.o ec_load.o ec_sign.o ec_verify.o
	ar ru $@ $^
	ranlib $@
libs: libhblk_crypto.a
clean:
	rm -f  *.o *.a
