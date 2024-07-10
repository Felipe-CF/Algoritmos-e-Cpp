/* consumidor: Programa exemplo de memória compartilhada */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <cstdio> // Para o std::putchar

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
    shm_fd = shm_open(name, O_RDWR, 0666);
    
    /* Mapeia a área para acesso via ponteiro */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    /* Lê da área de memória compartilhada */
    char *s;
    for (s = static_cast<char*>(ptr); *s != static_cast<char>(0); s++)
        std::putchar(*s);
    std::putchar('\n');
    
    /* Escreve na área de memória compartilhada */
    s=static_cast<char*>(ptr);

    *s='*';
    
    exit(0);
}






