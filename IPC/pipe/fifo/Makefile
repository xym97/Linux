.PHONY:all

all: client server

client:client_fifo.c
	gcc -o $@ $^

server:server_fifo.c
	gcc -o $@ $^

.PHONY:clean

clean:
	rm -f client server mypipe
