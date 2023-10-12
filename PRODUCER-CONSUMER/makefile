CC = g++

TARGET = source
INPUT = datafile.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET) -lpthread

clean:
	rm $(TARGET)

test:
	./$(TARGET)