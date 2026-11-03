#include "commands.h"
#include "edit.h"
#include "parser.h"
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char comando[100];
char mensagem[100] = "";
char resposta[10] = "";
char comando_rodar[512];

void abrir_shell(void) {
  char *shell = getenv("SHELL");

  if (shell == NULL || shell[0] == '\0') {
    shell = "/bin/sh";
  }

  def_prog_mode();
  endwin();

  pid_t pid = fork();

  if (pid == 0) {
    execl(shell, shell, (char *)NULL);
    _exit(127);
  }

  if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  }

  reset_prog_mode();
  refresh();
  clear();
}

void commands(int tecla, int l, const char *nome_arquivo) {
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

    else if (strncmp(comando, "cmd ", 4) == 0) {
      char *comando_shell = comando + 4;

      def_prog_mode();
      endwin();
      system(comando_shell);

      printf("\nPressione enter para voltar...");
      (void)getchar();
      reset_prog_mode();
      refresh();
    }

    else if (strcmp(comando, "shell") == 0) {
      abrir_shell();
    }

    else if (strcmp(comando, "run") == 0) {
      if (parser_run(comando_rodar, sizeof(comando_rodar)) == 1) {
        def_prog_mode();
        endwin();
        system(comando_rodar);
        printf("\nPressione ENTER para voltar ao editor...");
        (void)getchar();
        reset_prog_mode();
        refresh();
      }

      else {
        printf("RUN nao encontrado\n");
      }
    }
  }
}
