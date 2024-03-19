#include <iostream>
// #include <fstream>
 #include <fcntl.h>
 #include <unistd.h>
 #include<sys/stat.h>
using namespace std;

off_t tamanho_arqv(int descritor_de_arquivo){
        struct stat st; // declaro o struct stat para pode obter informações sobre o arquivo em especifíco
        int arquivo_info = fstat(descritor_de_arquivo, &st); // usei o descritor para acessar o arquivo que eu queria as infos
        if(arquivo_info == -1){// se o valor for -1 significa que houve erro
            cout << "Não foi possível ler informações do arquivo de origem" << endl;
            return 0;
        } 
        // foi possível obter informações!
        return st.st_size; 
        // o valor armazenado aqui é referente
        // a quantidade de bytes do tamanho do arquivo; será necessário como parametro na função read()
}

int main(int argc, char* argv[]){
    if(argc == 1){ // erro se nenhum arquivo for passado para o cp
        cout << "cp: missing file operand\n" << "Try 'cp --help' for more information." << endl;
        return 1;
    } 

    else{ // foram passados arquivos na "chamada" 
        int descrito_arquivo_origem = open(argv[1], O_RDONLY); // abro o arquivo e ele me retorna o descritor do mesmo
        if(descrito_arquivo_origem == -1){ // -1 indica erro
        cout << "arquivo de origem não foi aberto" << endl;
        return 1;
        }

        off_t tamanho_arquivo_origem = tamanho_arqv(descrito_arquivo_origem);
        // faço  verificações referentes a abertura do arquivo, depois pego suas informações e obtenho o tamanho dele em bytes
        // isso vai ajudar na hora de usar as funções read() e write() mais abaixo
        if(tamanho_arquivo_origem == 0)
            return 1;
        close(descrito_arquivo_origem); // fecho o arquivo de origem lido
        // já tenho seu identificador e vou usar para as restantes operações

        char* conteudo_origem = new char[tamanho_arquivo_origem];
        ssize_t conteudo_lido = read(descrito_arquivo_origem, &conteudo_origem, tamanho_arquivo_origem);
        // para essa função é necessário o descritor, um array para armazenar o conteúdo do arquivo
        // e o tamanho desse array para poder ler o conteúdo do arquivo

        // checagem do retorno do read()
        if(conteudo_lido == -1){ // -1 indica problema na leitura do arquivo
            cout << "Problema na leitura do arquivo de origem" << endl; return 1;
            delete [] conteudo_origem;
            close(descrito_arquivo_origem); // arquivo de origem é fechado após a leitura dele
            return 1;
        }

// ---     agora "repito" os  passos acima, mas para o arquivo destino (gravar) ---

        int descrito_arquivo_destino = open(argv[2], O_WRONLY); 
        if(descrito_arquivo_destino == -1)
            cout << "arquivo de origem não foi aberto" << endl; return 1;
        
        ssize_t conteudo_gravado = write(descrito_arquivo_destino, conteudo_origem, tamanho_arquivo_origem);
        if(conteudo_gravado == -1)
            cout << "arquivo de destino não pode ser gravado" << endl;
        close(descrito_arquivo_destino);
        close(descrito_arquivo_origem); // arquivo de origem é fechado após a leitura dele
    }
}

