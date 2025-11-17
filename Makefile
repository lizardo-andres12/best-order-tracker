compile: main.cpp
	g++ -Wall -Werror -pedantic-errors -O3 -march=native main.cpp -o main.out

run: main.out test.txt
	./main.out < test.txt

clean:
	@rm -rf *.out *.o
