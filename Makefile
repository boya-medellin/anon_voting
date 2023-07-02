CC = gcc
CFLAGS = -lm
TARGET = anon_voting

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c $(TARGET).h $(CFLAGS)

clean: 
	$(RM) $(TARGET)
