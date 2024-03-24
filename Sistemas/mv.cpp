#include <iostream>
#include <unistd.h>
#include <dirent.h>

using namespace std;


int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "mv: missing file operand\n" << "Try 'mv --help' for more information."<< endl;
        return 1;
    }
    if(argc == 2){
        cout << "mv: missing destination file operand after '" << argv[1] <<"'\n" << "Try 'mv --help' for more information." <<endl;
        return 1;
    }

    // todos os parametros necessários foram passados
    string origem = argv[1];
    string destino = argv[2];
    for(int i = 0; i < origem.length; i++){
        
    }
    if(argv[1] == argv[2]){
        cout << "mv: " << argv[1]  <<"' and '" <<  argv[2] <<"' are teh same file" <<endl;
        return 1;
    }
    // else{
    //     int diretorio_destino = chdir(argv[2]); // tento mudar o diretorio de trabalho para o 2° argumento passado na execução do código
    //     // caso seja passado um nome do arquivo
    //     if(errno != ENOENT){
    //         cout << "problema ao encontrar o diretorio ou nome do arquivo passado como destino" << endl;
    //         return 1;
    //     }
    //     else{

    //     }


    // }
    //     char buffer[1024];
    //     char* caminho = getcwd(buffer, 1024);
    //     DIR *diretorio = opendir(caminho); 
    //     dirent *dir = readdir(diretorio); 
    // dir = readdir(diretorio);
    // dir = readdir(diretorio);
    // dir = readdir(diretorio);
    // dir = readdir(diretorio);
    // dir = readdir(diretorio);
    
    return 0;
}