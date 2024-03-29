#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
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


// não funciona mover diretorio
// também não quero saber o porque, são 01hrs da sexta-feira santa

int main(int argc, char* argv[]){
    if(argc == 1){ // nenhum parametro passado
        cout << "mv: missing file operand\n" << "Try 'mv --help' for more information."<< endl;
        return 1;
    }
    if(argc == 2){ // um parametro passado
        cout << "mv: missing destination file operand after '" << argv[1] <<"'\n" << "Try 'mv --help' for more information." <<endl;
        return 1;
    }

    // todos os parametros necessários foram passados!

    // Tratar erro1
    // agora eu checo se eles são iguais e imprimo o erro correspondente
    string arg1 = argv[1];
    string arg2 = argv[2];
    if(arg1 == arg2){
        cout << "mv: " << argv[1]  <<"' and '" <<  argv[2] <<"' are the same file" <<endl;
        return 1;
    }
    if(std::filesystem::is_directory(argv[1])){
        if(!open(argv[2], O_RDONLY)){
            cout << "digite o caminho de um diretorio, não de um arquivo no lugar de " << argv[2] << endl;
            return 1;
        }
        std::filesystem::copy(argv[1], argv[2]);
        std::filesystem::remove(argv[1]);
    }

    else{
        
        int arqv_origem = open(argv[1], O_RDONLY | O_NONBLOCK);
        if(arqv_origem == -1){
            cout << "problema ao abir " << argv[1] << endl;
            return 1;
            }
        off_t tam_orig = tamanho_arqv(arqv_origem);
        char* cont = new char[tam_orig];
        ssize_t cont_lido = read(arqv_origem, cont, tam_orig);
        if(cont_lido == -1){
            cout << "problema ler 1" << endl;
            return 1;
            }

        if(std::filesystem::is_directory(argv[2])){
            std::filesystem::copy(argv[1], argv[2]);
            std::filesystem::remove(argv[1]);
            close(arqv_origem);
            delete[] cont;
            }
        else{ 
            int arqv_dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT | O_NONBLOCK);
            if(arqv_dest == -1){
                cout << "problema ler 2" << endl;
                return 1;
            }
            ssize_t grave = write(arqv_dest, cont, tam_orig);
            if(grave == -1){
                cout << "problema grave" << endl;
                return 1;
            }
            int remove = unlink(argv[1]);
            if(remove == -1){
                cout << "problema remove" << endl;
                return 1;
            } 
            close(arqv_origem);
            close(arqv_dest);
            delete[] cont;

            }
    }

    
    return 0;
    
}



