all:
	gcc -o main -g -Wall -Wextra main.c

test:
	gcc -g -Wall -Wextra test.c -o test
