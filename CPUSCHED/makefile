CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp FIFO.cpp SJF.cpp
	$(CC) $(TARGET).cpp FIFO.cpp SJF.cpp -o $(TARGET)

clean:
	rm $(TARGET)

test:
	./$(TARGET) $(INPUT)