all: data_management.o simulation.o
	gcc data_management.o simulation.o src/include/common.h src/sequential.c -o main

data_management.o: src/include/data_management.h
	gcc -c src/data_management.c

simulation.o: src/include/simulation.h
	gcc -c src/simulation.c

clean:
	rm -rf *.o
	rm -rf main

run:
	./main instances/test.txt