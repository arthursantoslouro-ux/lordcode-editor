CC = clang
CFLAGS = -Wall -Wextra
TARGET = lordcode

all: $(TARGET)

$(TARGET): src/lordcode.c
	$(CC) $(CFLAGS) src/alert.c src/parser.c src/menu.c src/commands.c src/syntax.c src/lordcode.c src/edit.c -o $(TARGET) -lncurses

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

