#include "commands.h"
#include <ncurses.h>

char comando[100];

void commands(int tecla, int l) {
  if (tecla == '$') {
    mvhline(LINES - 1, 0, ' ', l);
    mvprintw(LINES - 1, 0, "$ ");
    refresh();

    move(LINES - 1, 2);
    echo();
    wgetnstr(stdscr, comando, sizeof(comando) - 1);
    noecho();
  }
}
