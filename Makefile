CC=g++ -g -Wall

a: main.o puma.o tc_time.o 
	$(CC) main.o puma.o tc_time.o -o a 

main.o: main.cpp puma.h tc_time.h
	$(CC)  -c  main.cpp

puma.o: puma.cpp puma.h tc_time.h
	$(CC)  -c  puma.cpp



tc_time.o: tc_time.cpp tc_time.h 
	$(CC)  -c tc_time.cpp

clean:
	rm *.o QtoF2