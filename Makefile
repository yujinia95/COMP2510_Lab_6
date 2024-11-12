CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = student.o main.o
TARGET = students

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~