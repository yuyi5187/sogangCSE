all: hw1_kmp hw1_naive
cc=gcc
TARGET=hw1_kmp hw1_naive

hw1_kmp: hw1_kmp.c
	$(CC) -o $@ $<
hw1_naive: hw1_naive.c
	$(CC) -o $@ $<

hw1_kmp.o: hw1_kmp.c
	$(CC) -c -o hw1_kmp.o hw1_kmp.c

hw1_naive.o: hw1_naive.c
	$(CC) -c -o hw1_naive.o hw1_naive.c

clean:
	rm $(TARGET)