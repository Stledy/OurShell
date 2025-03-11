CC=gcc
CFLAGS=-Wall
TARGET=ourshell

all: $(TARGET)

$(TARGET): ourshell.c
	$(CC) $(CFLAGS) -o $(TARGET) ourshell.c

clean:
	rm -f $(TARGET)
