CC=g++ -g -Wall

QtoF2: PolyFromQtoF2.o Types.o File.o 
	$(CC) PolyFromQtoF2.o Types.o File.o puma.o tc_time.o -o QtoF2 



PolyFromQtoF2.o: PolyFromQtoF2.cpp 
	$(CC)  -c  PolyFromQtoF2.cpp

Types.o: Types.cpp Types.h 
	$(CC)  -c Types.cpp

File.o: File.cpp File.h 
	$(CC)  -c File.cpp

puma.o: puma.cpp puma.h 
	$(CC)  -c  puma.cpp



tc_time.o: tc_time.cpp tc_time.h 
	$(CC)  -c tc_time.cpp

clean:
	rm *.o QtoF2