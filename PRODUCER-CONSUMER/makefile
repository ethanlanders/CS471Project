CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	make clean ; $(CC) $(TARGET).cpp threads.h -o $(TARGET) -lpthread

clean:
	rm $(TARGET)

test:
	make ; ./$(TARGET)