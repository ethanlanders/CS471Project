CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET)

clean:
	rm $(TARGET)

test:
	./$(TARGET) $(INPUT)