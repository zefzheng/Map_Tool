all: map1 map2

map1: main.o buildTree.o searchData.o printout.o read_CSV.o
	gcc -o map1 main.o buildTree.o searchData.o printout.o read_CSV.o -g -lm

map2: main.o buildTree.o searchData.o printout.o read_CSV.o
	gcc -o map2 main.o buildTree.o searchData.o printout.o read_CSV.o -g -lm

main.o: main.c
	gcc -c -Wall main.c -g -lm

buildTree.o: buildTree.c
	gcc -c -Wall buildTree.c -g -lm

searchData.o: searchData.c
	gcc -c -Wall searchData.c -g -lm

printout.o: printout.c
	gcc -c -Wall printout.c -g -lm

read_CSV.o: read_CSV.c
	gcc -c -Wall read_CSV.c -g -lm
