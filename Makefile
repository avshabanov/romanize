
CC			?=	gcc
CFLAGS	?=	-std=c99 -Wall

LINKER	?=	gcc
LFLAGS	?=

.PHONY: all
all: target/romanize

target/romanize: target/o/romanize.o
	$(LINKER) -o target/romanize target/o/romanize.o $(LFLAGS)

target/o/romanize.o: target/o romanize.c
	$(CC) $(CFLAGS) -c romanize.c -o target/o/romanize.o

# Object files
target/o: target
	mkdir target/o

target:
	mkdir target

.PHONY: clean
clean:
	rm -rf target
