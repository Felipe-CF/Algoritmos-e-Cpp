#include <sys/sysinfo.h>
#include <iostream>

using namespace std;
int main(){

    struct sysinfo info_sistema;
    sysinfo(&info_sistema);
    int h = info_sistema.uptime/3600;
    int m = (info_sistema.uptime%3600) / 60;
    int s = (info_sistema.uptime%3600) % 60;
    cout << "Tempo de uso: " << h << ":" << m << ":" << s << "hrs" << endl;

}