#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){

    if(argc == 1)
        cout << "cp: missing file operand\n" << "Try 'cp --help' for more information." << endl;
    else{
        std::ifstream origem;
        origem.open(argv[1]);
    }
    // string s(argv[0]);


}