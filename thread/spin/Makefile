all:testspin testmutex

testmutex:pthread_mutex.c
	gcc -o $@ $^ -lpthread

testspin:pthread_spin.c
	gcc -o $@ $^ -lpthread


.PHONY:clean

clean:
	rm -f testspin testmutex



