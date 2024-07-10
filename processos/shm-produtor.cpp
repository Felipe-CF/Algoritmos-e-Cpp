/* produtor: Programa exemplo de memória compartilhada */
#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>


int main(){
    /* Tamanho (em bytes) da memória compartilhada */
    const int SIZE = 27;
    
    /* Nome da área de memória compartilhada */
    const char* name = "OS";
    
    /* fd (File Descriptor) da memória compartilhda */
    int shm_fd;
    
    /* Ponteiro para a área compartilhada */
    void* ptr;
    
    /* Abre a área de memória */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    /* Configura o tamanho da área */
    ftruncate(shm_fd, SIZE);
   
    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
   
   /* crio um ponteiro char para a opsição 0 da area de memoria */
    char *s = static_cast<char *>(ptr);
    char c;

    /* Escreve na área os caracteres de 'a' a 'z' */
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    
    /* insere 0 no final */
    *s = (char)0;

    /* retorno para a posição 0 da area mapeada*/
    s = static_cast<char*>(ptr);

    /* fica aguardando o processo consumidor terminar*/
    while (*s != '*') sleep(1);
   
    /* Remove memória compartilhada */
    shm_unlink(name);
    exit(0);
}