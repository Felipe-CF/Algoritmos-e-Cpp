#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

string dia_semana[] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};
string mes[] = {"Jan", "Fev", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int main() {
    // Obter o tempo atual em segundos desde o Unix Epoch
    time_t t;
    t = time(&t); // retorna os segundos que se passaram desde 00:00 01/01/1970

    struct tm* tempo_agora;
    tempo_agora = localtime(&t); // converte o tipo "time_t" para struct tm
    // nesse struct se tem informações como horario e data

    // nesse caso optei por pegar os campos que compõe o struct e formatar a saída 
    cout << dia_semana[tempo_agora->tm_wday] << " " << mes[tempo_agora->tm_mon] << " " << tempo_agora->tm_mday << " ";
    cout << tempo_agora->tm_hour << ":" << tempo_agora->tm_min << ":" << tempo_agora->tm_sec << " ";
    cout << tempo_agora->tm_year+1900 << endl;

    // "mas não imprime o fuso" quem se preocupa com fuso é piloto de avião ;)
    
    return 0;
}
