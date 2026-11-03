#include "alert.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

static char alerta_texto[256] = "";
static short alerta_cor = COLOR_GREEN;
static time_t alerta_expira = 0;

void alert(const char *mensagem, short cor_fundo) {
  snprintf(alerta_texto, sizeof(alerta_texto), "%s", mensagem);
  alerta_cor = cor_fundo;

  alerta_expira = time(NULL) + 1;
}

void alert_draw(void) {
  if (alerta_texto[0] == '\0') {
    return;
  }

  if (time(NULL) >= alerta_expira) {
    alerta_texto[0] = '\0';
    return;
  }

  init_pair(20, COLOR_BLACK, alerta_cor);

  attron(COLOR_PAIR(20));
  mvhline(LINES - 1, 0, ' ', COLS);
  mvaddnstr(LINES - 1, 0, alerta_texto, COLS);
  attroff(COLOR_PAIR(20));
}
