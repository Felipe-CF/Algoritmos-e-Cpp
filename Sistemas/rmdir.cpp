#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "mkdir: missing operand\n" << "Try 'mkdir --help' for more information." << endl;
        return 1;
    }
    int r;
    for(int i = 1; i <= argc; i++){
        r = rmdir(argv[i]);
        if(errno == ENOTDIR){ // argv[i] não é dir
            cout << "rmdir: failed to remove '" << argv[i] << "': Not a directory" << endl;
        }
        if(errno == ENOTEMPTY){ // argv[i] não é vazio
            cout << "rmdir: failed to remove '" << argv[i] << "': Directory not empty" << endl;
        }
        else if(errno == ENOENT){ // argv[i] não foi encontrado
            cout << "rmdir: failed to remove '" << argv[i] << "': No such file or directory" << endl;
        }

    }
    return 0;
}