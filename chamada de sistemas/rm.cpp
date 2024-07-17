#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1) // verifico se foi passado algum caminho/nome referente ao arquivo
        cout << "rm: missing operand" << "Try 'rm --help' for more information." <<  endl; // se não foi imprimo mesnagem de erro

    else{
        int procura_arquivo = open(argv[1], O_RDONLY); // tento abrir o arquivo através do caminho passado
        if(procura_arquivo == -1){ // checa se houve erro na tentava de abrir o arquivo
            cout << "rm: cannot remove '"<< argv[1] << "': No such file or directory" << endl;
            return 1;
        }
        
// ----     o arquivo foi aberto/localizado
        int remove_arquivo = unlink(argv[1]); // o caminho é passado para a função unlink()

        if(remove_arquivo == -1){
            cout << "arquivo não pode ser deletado" << endl;
        }
        close(procura_arquivo);
    }
    return 0;
}
