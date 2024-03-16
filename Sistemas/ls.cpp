#include <iostream>
#include <unistd.h>
#include <dirent.h>
using namespace std;

int main(int argc, char* argv[]){

    if(argc < 2){
    // pega o diretorio atual
        char buffer[1024];
        char* caminho = getcwd(buffer, 1024);
    // retorna o caminho do diretorio e retorna para o ponteiro
    // caminho

    // lendo o dir
        DIR *diretorio = opendir(caminho); // passo o caminho para o ponteiro do tipo DIR
        dirent *dir = readdir(diretorio); // ".."
    //  ^^ retorna a entrada do diretório pai do diretorio que se deseja ler e listar os arquivos
    // agora eu entendi o "cd.." que usava no terminal para sair de um diretorio
    // na verdade eu "não estava saindo" mas "entrando em outro"
    // (é redundantemente esclarecedora essa frase)
        dir = readdir(diretorio); // . --> to no diretorio desejado
    // DECIDI  repetir o comando até apresentar um erro, que imaginei ser quando não tivesse mais arquivos para ler
    // no diretorio e fui imprimindo o que era retornado:
        // dir = readdir(diretorio); // uptime.cpp
        // dir = readdir(diretorio); // ls
        // dir = readdir(diretorio); // date.cpp
        // dir = readdir(diretorio); // uptime
        // dir = readdir(diretorio); // date
        // dir = readdir(diretorio); // ls.cpp
        // dir = readdir(diretorio); // segmentation fault (core dumped)
    // ele tentou acessar um local de memória não permitido (um outro diretorio?)
    // imagino que o opnedir() limite "por onde pode andar" com readdir() a somente o caminho passado
    // o segmentation quando ocorre retorna NULL
        if(dir != NULL){
            while((dir = readdir(diretorio)) != NULL)
                cout << dir->d_name << " ";
            cout << endl; 
        }else{
            cout << "Diretorio não pode ser acessado" << endl;
        }

    }
    else{
        // lendo o dir
        DIR *diretorio = opendir(argv[1]); // passo o caminho para o ponteiro do tipo DIR
        dirent *dir = readdir(diretorio); // ".."
        dir = readdir(diretorio); 
        if(dir != NULL){
            while((dir = readdir(diretorio)) != NULL)
                cout << dir->d_name << " ";
            cout << endl; 
        }else{
            cout << "Diretorio não pode ser acessado" << endl;
        }
        //  cout << "eu" << endl; 
    }


}