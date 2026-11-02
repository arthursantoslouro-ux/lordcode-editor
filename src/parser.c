#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parser_run(char *destino, size_t tamanho) {
  char *home = getenv("HOME");

  if (home == NULL) {
    perror("HOME NAO ENCONTRADO");
    return 1;
  }

  char caminho[512];

  snprintf(caminho, sizeof(caminho), "%s/.lordcoderc", home);

  FILE *arquivo = fopen(caminho, "r");

  if (arquivo == NULL) {
    return 0;
  }

  char linha[512];

  while (fgets(linha, sizeof(linha), arquivo)) {
    char *inicio = linha;

    while (*inicio == ' ' || *inicio == '\t') {
      inicio++;
    }

    if (strncmp(inicio, "RUN", 3) != 0) {
      continue;
    }

    if (inicio[3] != ' ' && inicio[3] != '\t') {
      continue;
    }

    char *igual = strchr(inicio, '=');

    if (igual == NULL) {
      continue;
    }

    char *valor = igual + 1;

    while (*valor == ' ' || *valor == '\t') {
      valor++;
    }

    if (*valor != '"') {
      continue;
    }

    valor++;

    char *fim = strchr(valor, '"');

    if (fim == NULL) {
      continue;
    }

    *fim = '\0';

    snprintf(destino, tamanho, "%s", valor);

    fclose(arquivo);

    return 1;
  }

  fclose(arquivo);
  return 0;
}
