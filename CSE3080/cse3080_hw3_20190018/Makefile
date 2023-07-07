cc=gcc
TARGET=hw3

$(TARGET): hw3.o
	$(CC) -o $@ $<

hw3.o: hw3.c
	$(CC) -c -o hw3.o hw3.c

clean:
	rm *.o $(TARGET)