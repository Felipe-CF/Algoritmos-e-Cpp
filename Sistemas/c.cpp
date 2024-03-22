#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include<sys/stat.h>
using namespace std;

// faço verificações referentes a abertura do arquivo, depois pego suas informações e obtenho o tamanho dele em bytes
// isso vai ajudar na hora de usar as funções read() e write() mais abaixo
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
        int id_origem = open(argv[1], O_RDONLY); // abro o arquivo e ele me retorna 
        // o identificador único associado ao arquivo aberto.
        if(id_origem == -1){ // -1 indica erro
        cout << "arquivo de origem não foi aberto" << endl;
        return 1;
        }

        // pego o tamanho do arquivo - usei o off_t por ser um inteiro de 64 bits 
        // (um margem boa para armazenar o tamanho)
        off_t tamanho_origem = tamanho_arqv(id_origem);
    
        if(id_origem == 0)
            return 1;

        char* conteudo_origem = new char[tamanho_origem];
        ssize_t conteudo_lido = read(id_origem, conteudo_origem, tamanho_origem);
        // para essa função é necessário o descritor, um array para armazenar o conteúdo do arquivo
        // e o tamanho desse array para poder ler o conteúdo do arquivo
        cout <<  conteudo_origem << endl;
        close(id_origem); // arquivo de origem é fechado após a leitura dele
    }
}

