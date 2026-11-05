CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LDLIBS  = -lm
TARGET  = app
OBJS    = main.o math_funcs.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o: main.c math_funcs.h
	$(CC) $(CFLAGS) -c main.c -o main.o

math_funcs.o: math_funcs.c math_funcs.h
	$(CC) $(CFLAGS) -c math_funcs.c -o math_funcs.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
