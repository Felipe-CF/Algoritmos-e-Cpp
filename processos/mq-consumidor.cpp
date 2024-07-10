#define _XOPEN_SOURCE 500
#include <mqueue.h>
#include <assert.h>
#include <iostream>

int main(int argc, char **argv) {
    /* Abre a fila para leitura */
    mqd_t mqd = mq_open("/OpenCSF_MQ", O_RDONLY);
    assert(mqd != -1);

    /* Recupera os atributos da fila */
    struct mq_attr attr;
    assert(mq_getattr(mqd, &attr) != -1);

    char *buffer = new char[attr.mq_msgsize];
    assert(buffer != NULL);

    /* Recupera mensagem e  prioridade */
    unsigned int priority = 0;
    if ((mq_receive(mqd, buffer, attr.mq_msgsize,
                    &priority)) == -1)
        std::cerr << " [MQ ERROR] Falha ao receber mensagem\n";
    else
        std::cout << "Recebeu mensagem [prioridade "
                  << priority << "]: "
                  << buffer
                  << std::endl;

    /* Libera memória alocada, fecha e apaga a fila */
    delete[] buffer;
    mq_close(mqd);
    mq_unlink("/OpenCSF_MQ");
    exit(0);
}