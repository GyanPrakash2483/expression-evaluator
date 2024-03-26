CC		=	gcc
CCFLAGS	=	-lm -Iinclude -Wall -Werror -Wextra

build: src/expression.c src/notations.c src/stack.c src/preposteval.c
	$(CC) src/expression.c src/notations.c src/stack.c src/preposteval.c -o preposteval $(CCFLAGS)