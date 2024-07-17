#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
using namespace std;


// faço  verificações referentes a abertura do arquivo, depois pego o tamanho em bytes 
off_t tamanho_arqv(int descritor_de_arquivo){
        struct stat st; // me traz informações sobre o arquivo 

        int arquivo_info = fstat(descritor_de_arquivo, &st); // acesso o arquivo 
        
        if(arquivo_info == -1){
            cout << "Não foi possível ler informações do arquivo de origem" << endl;

            return -1;
        } 

        return st.st_size; 
}


int main(int argc, char ∗∗argv) {
    if(argc == 1){ // erro se nenhum arquivo for passado para o cp
        cout << "passe os parametros, meu querido\n" << endl;
        return -1;
    } 

    const char ∗ arquivo_original = argv[1];

    int id_arquivo = open(argv[1], O_RDONLY); // tento abrir o arquivo e checo se deu certo 

    if(id_arquivo == -1){ 
        cout << "arquivo de origem não foi aberto" << endl;

        return -1;
    }

    // pego o tamanho em bytes do arquivo aberto
    off_t tamanho_arquivo = tamanho_arqv(id_arquivo);

    char* conteudo = new char[tamanho_arquivo];

    ssize_t conteudo_lido = read(id_arquivo, conteudo, tamanho_arquivo);

    if(conteudo_lido == -1){ // checo a leitura do arquivo
        cout << "Problema na leitura do arquivo\n" << endl;

        delete [] conteudo;

        close(id_arquivo); // arquivo de origem é fechado

        return -1;
    }


    // agora eu irei criar a área de memória compartilhada
    const int = tamanho_area = ++tamanho_arquivo;

    const char* nome = "arquivo";

    int shm_descritor;

    void* ponteiro;

    shm_descritor = shm_open(nome, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_descritor, tamanho_area);

    ponteiro = mmap(0, tamanho_area, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    char *s = static_cast<char *>(ponteiro);

    for(int i = 0; i < tamanho_area; i++)
        *s++ = conteudo[i];



    const char ∗ targetfn = argv[2];

    int source = open(sourcefn,O_RDONLY);

    int target = open(targetfn,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

    char buf[SIZE-1];

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