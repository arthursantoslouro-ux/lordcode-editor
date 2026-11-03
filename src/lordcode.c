#include "edit.h"
#include "menu.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  initscr();
  srand(time(NULL));
  keypad(stdscr, TRUE);
  noecho();
  raw();

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);

  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);
  init_pair(7, COLOR_BLUE, COLOR_BLACK);
  init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(9, COLOR_CYAN, COLOR_BLACK);
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_CYAN, COLOR_BLACK);

  if (argc < 2) {
    menu();
    endwin();
    return 0;
  }

  bkgd(COLOR_PAIR(1));

  editar_arquivo(argv[1]);

  endwin();

  return 0;
}
