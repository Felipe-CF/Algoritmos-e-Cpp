#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char ∗∗argv) {
    const char ∗ sourcefn = argv[1];


    const char* nome = "arquivo";

    int shm_descritor;

    void* ponteiro;

    shm_descritor = shm_open(nome, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_descritor, 1025);

    ponteiro = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    const char ∗ targetfn = argv[2];

    int source = open(sourcefn,O_RDONLY);

    int target = open(targetfn,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

    char buf[1024];

    int s;

    while ((s=read(source,buf,1024))!=0)
        write(target,buf,s);

    close(target);

    close(source);

    return 0;
}



    // const char ∗ sourcefn = argv[1];

    // const char ∗ targetfn = argv[2];

    // int source = open(sourcefn,O_RDONLY);

    // int target = open(targetfn,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

    // char buf[1024];

    // int s;

    // while ((s=read(source,buf,1024))!=0)
    //     write(target,buf,s);

    // close(target);

    // close(source);