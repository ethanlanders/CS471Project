CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp
	$(CC) $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp -o $(TARGET)

clean:
	rm $(TARGET)

test:
	./$(TARGET) $(INPUT)