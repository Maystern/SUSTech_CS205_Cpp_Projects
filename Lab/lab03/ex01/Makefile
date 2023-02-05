CC = g++
TARGET = main
OBJ = main.o fib.o

CFLAGES = -c -Wall

$(TARGET) : $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGES) $< -o $@

.PHONY:clean
clean:
	rm -f *.o $(TARGET)