#!/bin/sh
TARGET=$1
THREADS=1

# build leveldb libs
cd ./leveldb
make libleveldb.a libmemenv.a -j$THREADS

cd ../
OPENSSL_INCLUDE_PATH=/usr/include/openssl-1.0 OPENSSL_LIB_PATH=/usr/lib/openssl-1.0 make -j$THREADS -f makefile.$TARGET all


