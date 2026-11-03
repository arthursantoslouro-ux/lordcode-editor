#include "syntax.h"
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

void highlight(const char *linha, int y) {
  int dentro_string = 0;
  const char *keywords[] = {"int",      "char",   "string",  "for",    "while",
                            "#include", "if",     "else if", "elif",   "else",
                            "continue", "float",  "const",   "printf", "print",
                            "#define",  "#ifdef", "#ifndef", "import", "def",
                            "return",   "size_t", "sizeof",  "void",   "static",
                            "struct"};

  int cores[] = {COLOR_PAIR(4), COLOR_PAIR(5), COLOR_PAIR(6),  COLOR_PAIR(7),
                 COLOR_PAIR(8), COLOR_PAIR(9), COLOR_PAIR(11), COLOR_PAIR(12)};

  int total_keywords = sizeof(keywords) / sizeof(keywords[0]);
  int total_cores = sizeof(cores) / sizeof(cores[0]);

  int coluna = 0;
  const char *posicao = linha;
  while (*posicao != '\0') {
    int encontrada = 0;

    if (dentro_string) {
      attron(COLOR_PAIR(6));
      mvaddch(y, coluna, *posicao);
      attroff(COLOR_PAIR(6));

      if (*posicao == '"') {
        dentro_string = 0;
      }
      posicao++;
      coluna++;
      continue;
    }

    if (*posicao == '"') {
      dentro_string = 1;
      attron(COLOR_PAIR(6));
      mvaddch(y, coluna, *posicao);
      attroff(COLOR_PAIR(6));

      posicao++;
      coluna++;
      continue;
    }

    for (int i = 0; i < total_keywords; i++) {
      size_t tamanho = strlen(keywords[i]);

      if (strncmp(posicao, keywords[i], tamanho) == 0) {
        attron(cores[i % total_cores]);

        mvaddnstr(y, coluna, posicao, tamanho);

        attroff(cores[i % total_cores]);

        posicao += tamanho;
        coluna += tamanho;

        encontrada = 1;
        break;
      }
    }

    if (!encontrada) {

      if (isdigit(*posicao)) {
        attron(COLOR_PAIR(12));
        mvaddch(y, coluna, *posicao);
        attroff(COLOR_PAIR(12));
      } else {
        mvaddch(y, coluna, *posicao);
      }
      posicao++;
      coluna++;
    }
  }
}
