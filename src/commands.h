#ifndef COMANDOS_H
#define COMANDOS_H

extern char mensagem[100];
extern char comando[100];

void abrir_shell(void);
void commands(int tecla, int l, const char *nome_arquivo, int alt);

#endif
