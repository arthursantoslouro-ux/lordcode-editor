#include "edit.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

FILE *arquivo;
char nome_arquivo[50];

void menu(void) {
  const char *opcoes[] = {"Abrir arquivo", "Sair"

  };

  int total = sizeof(opcoes) / sizeof(opcoes[0]);
  int selecionado = 0;
  int tecla;

  while (1) {
    clear();

    // attron(COLOR_PAIR(2) | A_BOLD);

    wbkgd(stdscr, COLOR_PAIR(12));


	mvaddstr(1, 2, "██╗      ██████╗ ██████╗ ██████╗  ██████╗ ██████╗ ██████╗ ███████╗");
	mvaddstr(2, 2, "██║     ██╔═══██╗██╔══██╗██╔══██╗██╔════╝██╔═══██╗██╔══██╗██╔════╝");
	mvaddstr(3, 2, "██║     ██║   ██║██████╔╝██║  ██║██║     ██║   ██║██║  ██║█████╗");
	mvaddstr(4, 2, "██║     ██║   ██║██╔══██╗██║  ██║██║     ██║   ██║██║  ██║██╔══╝");
	mvaddstr(5, 2, "███████╗╚██████╔╝██║  ██║██████╔╝╚██████╗╚██████╔╝██████╔╝███████╗");
	mvaddstr(6, 2, "╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝");


    for (int i = 0; i < total; i++) {

      if (i == selecionado) {
        attron(A_REVERSE);
        mvprintw(8 + i, 2, "> %s", opcoes[i]);
        attroff(A_REVERSE);
      } else {
        mvprintw(8 + i, 2, "%s", opcoes[i]);
      }
    }
    refresh();

    tecla = getch();

    if (tecla == 'q') {
      exit(0);
    }

    switch (tecla) {
    case KEY_UP:
      selecionado--;
      if (selecionado < 0)
        selecionado = 0;
      break;

    case KEY_DOWN:
      selecionado++;
      if (selecionado >= total)
        selecionado = 0;
      break;

    case 10:
    case KEY_ENTER:
      switch (selecionado) {
      case 0:
        mvprintw(8, 2, "insira o nome do arquivo: ");
        refresh();
        echo();

        wgetnstr(stdscr, nome_arquivo, sizeof(nome_arquivo) - 1);
        noecho();

        arquivo = fopen(nome_arquivo, "a+");
        wbkgd(stdscr, COLOR_PAIR(1));
        werase(stdscr);
        editar_arquivo(nome_arquivo);
        break;
      }

    case 1:
      printf("\033[2J\033[H");
      fflush(stdout);
      endwin();
      exit(0);
      break;
    }
  }
}
