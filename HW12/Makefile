CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = app
OBJ     = main.o temp_api.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c temp_api.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
