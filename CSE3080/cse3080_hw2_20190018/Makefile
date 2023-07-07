cc=gcc
TARGET=hw2

$(TARGET): hw2.o
	$(CC) -o $@ $<

hw2.o: hw2.c
	$(CC) -c -o hw2.o hw2.c

clean:
	rm *.o $(TARGET)