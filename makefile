CC=gcc
CFLAGS = -Wall -g -std=c99 -D_XOPEN_SOURCE=700

rebuild: clean all

all: server client

server: server.c 
	$(CC) server.c challenges.c -lm $(CFLAGS) -o server

client: client.c
	$(CC) client.c $(CFLAGS) -o client
	
cppcheck:
	cppcheck --quiet --enable=all --force --inconclusive .

pvs-studio: # docker run --security-opt seccomp:unconfined -v "${PWD}:/root" -ti -w /root agodio/itba-so:1.0
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze
	plog-converter -a '64:1,2,3;GA:1,2,3;OP:1,2,3' -t tasklist -o report.tasks PVS-Studio.log

format:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i

clean:
	rm -f server client

.PHONY: rebuild all cppcheck pvs-studio format clean