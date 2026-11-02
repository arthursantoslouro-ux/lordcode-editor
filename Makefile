CC = clang
CFLAGS = -Wall -Wextra
TARGET = lordit

all: $(TARGET)

$(TARGET): src/lordit.c
	$(CC) $(CFLAGS) src/menu.c src/commands.c src/syntax.c src/lordit.c src/edit.c -o $(TARGET) -lncurses

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

