#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include<sys/stat.h>
using namespace std;

off_t tamanho_arqv(int descritor_de_arquivo){
        struct stat st; // declaro o struct stat para pode obter informações sobre o arquivo em especifíco
        int arquivo_info = fstat(descritor_de_arquivo, &st); // usei o descritor para acessar o arquivo que eu queria as infos
        if(arquivo_info == -1){// se o valor for -1 significa que houve erro
            cout << "Não foi possível ler informações do arquivo de origem" << endl;
            return 1;
        } 
        // foi possível obter informações!
        return st.st_size; 
        // o valor armazenado aqui é referente
        // a quantidade de bytes do tamanho do arquivo; será necessário como parametro na função read()
}

int main(int argc, char* argv[]){
    if(argc==1){ // não foram passados argumentos?
         cout << "passe algum caminho de arquivo válido" << endl;
         return 1;
    }
    if(!std::filesystem::is_directory(argv[1])){ // não foi passado arquivo?
        cout << "cat: " << argv[1] << ": Is a directory" << endl;
        return 1;
    }
    if(!open(argv[1], O_RDONLY)){// não foi passado arquivo válido?
        cout << "cat: " << argv[1] << ": No such file or directory" << endl;
        return 1;
    }
    
    int arqv = open(argv[1], O_RDONLY); // abro o arquivo

    off_t tam = tamanho_arqv(arqv); // pego o tamanho dele

    char* cont = new char[tam]; // array para armazenar o conteudo

    ssize_t ler = read(open(argv[1], O_RDONLY), cont, tam); // leio o conteudo e armazeno

    for(off_t i = 0; i < tam; i++) //imprimo no terminal o conteudo
            cout << cont[i]; 
    close(arqv);
    delete[] cont;
    return 0;
}