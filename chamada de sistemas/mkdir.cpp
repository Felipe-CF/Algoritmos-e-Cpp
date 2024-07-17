#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <filesystem>
#include<sys/stat.h>
using namespace std;


int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "mkdir: missing operand\n" << "Try 'mkdir --help' for more information." << endl;
        return 1;
    }
    DIR* dir;
    struct dirent *checa;

    if((dir = opendir(argv[1])) || (open(argv[1], O_RDONLY) != -1)){
        cout <<"mkdir: cannot create directory '" << argv[1] << "' : File exists" << endl;
        return 1;
    } 

    int criou_dir = mkdir(argv[1], S_IRWXU | S_IRWXO | S_IRWXG);
    if(criou_dir == -1)
        cout << "problema ao criar o diretorio" << endl;

    return 0;
}