CC=g++ -g -Wall
head1=../../
head2=../../cplusplus
head3=../../cudd
head4=../../util
cpluslibpath=../../cplusplus/.libs
cpluslib=obj
libspath=../../cudd/.libs
lib1=cudd
lib2=util

QtoF2: PolyFromQtoF2.o Types.o File.o 
	$(CC) PolyFromQtoF2.o Types.o File.o -o QtoF2 -L $(cpluslibpath)  -l$(cpluslib) -L $(libspath) -l$(lib1) -l$(lib2) -lm


PolyFromQtoF2.o: PolyFromQtoF2.cpp 
	$(CC) -c -I $(head1) -I $(head2) -I $(head3) -I $(head4) PolyFromQtoF2.cpp

Types.o: Types.cpp Types.h 
	$(CC)  -c Types.cpp

File.o: File.cpp File.h 
	$(CC)  -c File.cpp

clean:
	rm *.o QtoF2


