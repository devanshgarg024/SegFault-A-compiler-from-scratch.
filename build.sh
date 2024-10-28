gcc main.c lexerf.c parserf.c codegeneratorf.c hashmap/hashmapoperators.c -c
gcc main.o lexerf.o parserf.o codegeneratorf.o hashmapoperators.o -o build
./build