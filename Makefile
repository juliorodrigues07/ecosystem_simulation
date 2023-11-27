all: data_management.o simulation.o
	gcc -Wall data_management.o simulation.o src/include/common.h src/main.c -o main -lgomp

data_management.o: src/include/data_management.h
	gcc -c src/data_management.c

simulation.o: src/include/simulation.h
	gcc -c -fopenmp src/simulation.c

clean:
	rm -rf *.o *.out *.output
	rm -rf main sequential

sequential:
	gcc -Wall src/main.c src/data_management.c src/simulation.c -fno-openmp -o sequential
	./sequential instances/test.txt

with_prof:
	gcc -Wall src/main.c src/data_management.c src/simulation.c -fno-openmp -xpg -p -o sequential
	./sequential instances/instance_3.txt
	gprof sequential > report.output

parallel:
	./main instances/test.txt