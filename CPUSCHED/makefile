CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp
	$(CC) $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp helper_Functions.h -o $(TARGET)

clean:
	rm $(TARGET) FIFO.txt SJF.txt preemptive.txt

test:
	./$(TARGET) $(INPUT)