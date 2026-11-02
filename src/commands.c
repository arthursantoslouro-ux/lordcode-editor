#include "commands.h"
#include "edit.h"
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char comando[100];
char mensagem[100] = "";
char resposta[10] = "";

void commands(int tecla, int l, const char *nome_arquivo, int alt) {
  if (tecla == '$') {
    mvhline(LINES - 1, 0, ' ', l);
    mvprintw(LINES - 1, 0, "$ ");
    refresh();

    move(LINES - 1, 2);
    echo();
    wgetnstr(stdscr, comando, sizeof(comando) - 1);
    noecho();

    if (strcmp(comando, "save") == 0) {
      salvar_arquivo(nome_arquivo);
    }

    else if (strcmp(comando, "quit") == 0) {
      endwin();
      exit(0);
    }

    else if (strncmp(comando, "open ", 5) == 0) {
      char *caminho = comando + 5;

      if (caminho[0] != '\0') {
        editar_arquivo(caminho);
      }

      else {
        snprintf(mensagem, sizeof(mensagem), "Uso: $open caminho");
      }

    }

    else if (strcmp(comando, "clear") == 0) {
      snprintf(mensagem, sizeof(mensagem),
               "deseja limpar todo o arquivo [y/n]: ");
      move(LINES - 1, 0);
      clrtoeol();
      printw("%s", mensagem);
      refresh();

      echo();
      wgetnstr(stdscr, resposta, sizeof(resposta) - 1);
      noecho();

      if (strcmp(resposta, "y") == 0 || strcmp(resposta, "Y") == 0) {

        for (size_t i = 0; i < total_de_linhas; i++) {
          buffer[i][0] = '\0';
        }

        total_de_linhas = 1;
        arquivo_salvo = 0;

      }

      else if (strcmp(resposta, "n") == 0 || strcmp(resposta, "N") == 0) {
        snprintf(mensagem, sizeof(mensagem), "Operacao cancelada!");
      }

      else {
        snprintf(mensagem, sizeof(mensagem), "Resposta invalida");
      }
    }
  }
}
