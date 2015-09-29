local_path=$(pwd);

if [ ! -d protobuf-2.4.1 ]; then
	cp -f ../../../../bigfile/protobuf-2.4.1.tar.bz2 protobuf-2.4.1.tar.bz2;
	tar xvf protobuf-2.4.1.tar.bz2;
	rm protobuf-2.4.1.tar.bz2;
fi

cd protobuf-2.4.1;

./configure --prefix=$local_path/protobuf-2.4.1;
make;
make check;
make install;

mkdir -p ../../../../dependencies/lib/gcc;
cp src/.libs/libprotobuf.so* ../../../../dependencies/lib/gcc/;
cp src/.libs/libprotobuf-lite.so* ../../../../dependencies/lib/gcc/;

mkdir -p ../../../../dependencies/bin/gcc;
cp src/.libs/protoc ../../../../dependencies/bin/gcc/;
cp src/.libs/protoc.so* ../../../../dependencies/bin/gcc/;

mkdir -p ../../../../dependencies/inc/libprotobuf/google;
cp -r src/google/* ../../../../dependencies/inc/libprotobuf/google/;

cd ..;