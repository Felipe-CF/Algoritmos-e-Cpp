#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <fcntl.h>
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

int checa_diretorio(string diretorio, string caminho){
    char* caminho = diretorio;
    diretorio = diretorio[diretorio.length()-1]; 


        if(diretorio == "/"){ // foi passado apenas o caminho de um diretório
            int muda_dir = chdir(caminho); // mudo para ele
            char buffer[1024];
            char* caminho = getcwd(buffer, 1024);
            if(errno == ENOENT){ // trato o erro do diretorio ter sido passado errado
                cout << "diretório informado não existe " << endl;
                return 1;
            }
            cout << caminho << endl;
        }
        
        char buffer[1024];
        char* caminho = getcwd(buffer, 1024);
        cout << caminho << endl;
    return 1;
}


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
    // agora eu checo se eles são iguais e imprimo o erro correspondente
    string origem = argv[1];
    string destino = argv[2];
    if(origem == destino){
        cout << "mv: " << argv[1]  <<"' and '" <<  argv[2] <<"' are the same file" <<endl;
        return 1;
    }

    // parametros diferentes!
    // começa a parte de definir qual operação será feita: renomear ou mover p/ outro diretorio

    else{
        // a chamada mv se comporta dessa maneira:
        // 1- se voce passar 2 nomes de arquivo (sem caminho) o arquivo terá o nome alterado
        // 2- se voce passar 1 nome e um diretório ele será movido
        // 3- se  ||    ||   1  ||  e caminho para um arquivo existente ele sobrescreve este último
        // 4- ||  ||    ||   1  ||  e    ||    ||  ||   ||  não  ||      ||  move e altera o nome do arquivo

        
        // checando se um diretorio foi passado, ao inves do caminho de um arquivo
        



        // a partir daqui estamos em 2 situações:
        // 1- o diretorio passado com destino existe e o chdir() funcionou
        // 2- o objetivo é mudar o nome do arquivo 
        int arqv_origem = open(argv[1], O_RDONLY); // verifico se o 1° arquivo passsado realmente existe
        if(errno == ENOENT){ 
            cout << "mv: cannot stat '" << argv[1] << "': No such file or directory" << endl;
            return 1;
        }
        
        int arqv_destino1 = open(argv[2], O_RDWR | O_CREAT); // verifico se o 2° arquivo passsado realmente existe
        // o erro ENOENT informa que "No such file or directory"
        // nesse caso o O_CREATE me garante que o caminho passado foi errado
        // porque se estivesse correto ele teria criado um arquivo no diretorio de destino
        // se estiver correto, o arquivo com o nome novo já é criado
        if(arqv_destino1 != -1){  
            cout << "Já existe um arquivo com esse nome no diretorio" << endl;
            return 1;
        }
        close(arqv_destino1);

        int arqv_destino = creat(argv[2],  O_RDWR); // O 2° arquivo passsado não existe, então eu crio ele
        if(arqv_destino == -1){  
            cout << "mv: cannot stat '" << argv[1] << "': No such file or directory" << "1" << endl;
            return 1;
        }

        int tam_conteudo = tamanho_arqv(arqv_origem); // pego o tamanho do arquivo de origem
        char* conteudo = new char[tam_conteudo]; // conteudo do arquivo
        ssize_t conteudo_lido = read(arqv_origem, conteudo, tam_conteudo);
        // para essa função é necessário o descritor, um array para armazenar o conteúdo do arquivo
        // e o tamanho desse array para poder ler o conteúdo do arquivo
        //cout <<  conteudo_origem[0] << endl

        if(conteudo_lido == -1){ // -1 indica problema na leitura do arquivo
            cout << "Problema na leitura do arquivo de origem" << endl;
            delete [] conteudo;
            close(arqv_origem); // arquivo de origem é fechado após a leitura dele
            return 1;
        }

        ssize_t gravando_conteudo = write(arqv_destino, conteudo, tam_conteudo); 
        // gravo o conteudo do arquivo do origem no novo arquivo
        // se houver um erro ele retorna -1 e 
        
        if( gravando_conteudo == -1){
            cout << "arquivo de destino não pode ser gravado" << endl;
            delete [] conteudo;
            close(arqv_destino); // arquivo de origem é fechado após a leitura dele
            return 1;
        }
    int remover_arquivo_origem = unlink(argv[1]);
    delete[] conteudo;
    close(arqv_origem);
    close(arqv_destino);
    
    return 0;
    }
}



