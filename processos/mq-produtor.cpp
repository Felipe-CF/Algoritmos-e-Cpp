/* Produtor - Fia de mensagens */
#define _XOPEN_SOURCE 500
#include <mqueue.h>
#include <string.h>
#include <iostream>

int main(int argc, char **argv) {

  /* Criar fila de mensagem para escrita */
  mqd_t mqd = mq_open("/OpenCSF_MQ", 
                      O_CREAT | O_EXCL | O_WRONLY,
                      0600, NULL);
  /* Verificar se criação da fila ocorreu bem */
  if (mqd == -1) {
    std::cerr << "mq_open() failed" << std::endl;
    exit(1);
  }
  char msg[30];
  char *s = msg;
  for (char c = 'a'; c <= 'z'; c++)
    *s++ = c;
  *s = static_cast<char>(0);
  /* Enviar "abcdefghijklmnopqrstuvxwyz"
    como mensagem
    com prioridade 10,
    depois fecha a fila. */
  mq_send(mqd, msg, strlen(msg), 10);
  mq_close(mqd);
  exit(0);
}