CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp
	$(CC) $(TARGET).cpp FIFO.cpp SJF.cpp preemptive.cpp helper_Functions.h -o $(TARGET)

clean:
	rm $(TARGET) Output-FIFOScheduling.txt Output-PriorityScheduling.txt Output-SJFScheduling.txt

test:
	./$(TARGET) $(INPUT)