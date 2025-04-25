CC = gcc
CFLAGS = -Wall -Wextra
TARGET = OurShell
SRC = ourshell.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean