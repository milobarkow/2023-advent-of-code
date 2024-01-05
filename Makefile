WARN_FLAGS := -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -Wno-unused-variable

all:
	gcc -o main -g $(WARN_FLAGS) main.c

test:
	gcc -g -Wall -Wextra test.c -o test
