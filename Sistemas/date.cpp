#include <iostream>
#include <ctime>

int main() {
    // Obter o tempo atual em segundos desde o Unix Epoch
    time_t t;
    t = time(&t); // retorna os segundos que se passaram desde 00:00 01/01/1970

    struct tm* tempo_agora;
    tempo_agora = localtime(&t); // converte o tipo "time_t" para struct tm
    // nesse struct se tem informações como horario e data

    std::cout << tempo_agora->tm_hour-3 << ":" << tempo_agora->tm_min << ":" << tempo_agora->tm_sec <<  " hrs" << std::endl;
    // asctime() converte o struct em string
    // nesse caso optei por pegar os campos que compõe o struct e formatar a saída 
    return 0;
}
