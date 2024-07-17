#include <sys/sysinfo.h>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;
int main(){

     // Obter o tempo atual em segundos desde o Unix Epoch
    time_t t;
    t = time(&t); // retorna os segundos que se passaram desde 00:00 01/01/1970

    struct tm* tempo_agora;
    tempo_agora = localtime(&t); // converte o tipo "time_t" para struct tm
    // nesse struct se tem informações como horario e data
    cout << " " << tempo_agora->tm_hour << ":" << tempo_agora->tm_min << ":" << tempo_agora->tm_sec << " ";

    struct sysinfo info_sistema;
    sysinfo(&info_sistema);

    cout << "up " << info_sistema.uptime/3600 << ":" << (info_sistema.uptime%3600) / 60 << endl;

}