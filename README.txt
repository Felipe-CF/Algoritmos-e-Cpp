Explicação das implementações das chamadas de sistemas - Linux
(os possíveis erros foram tratados em cada código, em sua maioria semelhantes a chamada de sistema)
(também os arquivos menores não foram plenamente comentados pela leitura ser simples)
--> Das 11 chamadas pedidas 9 foram implementadas, e abaixo estão as explicações de cada uma.
date:
    Usando time_t podemos obter o tempo passado, em segundos, desde 00:00 01/01/1970. Depois, converto
    para o struct tm, que tem informações de horario e data. 
      int tm_sec;   // segundos após o minuto (0 - 61)
      int tm_min;   // minutos após a hora (0 - 59)
      int tm_hour;  // horas desde a meia-noite (0 - 23)
      int tm_mday;  // dia do mês (1 - 31)
      int tm_mon;   // meses desde janeiro (0 - 11) (usado como indice de um array com os meses)
      int tm_wday;  // dias desde domingo (0 - 6) (usado como indice de um array com os dias)
      int tm_year;  // anos desde 1900
    Depois disso, manipulo a impressão igual a chamada.

uptime:
    Usando time_t podemos obter o tempo passado, em segundos, desde 00:00 01/01/1970. Depois, converto
    para o struct tm, que tem informações de horario e data. Assim pego a hora atual.
    O struct sysinfo permite pegar o tempo (em segundos) que o computador está ligado
    Depois disso, manipulo a impressão igual a chamada.
    (caso conste menos funcionalidades que o desejado a explicação é só uma: cansaço de correr atrás)

ls:
    Usando getcwd() eu pego o caminho do diretorio atual, passo ele como parametro de opendir(), passando seu retorno
    para um ponteiro DIR; depois eu uso ele como parametro de um dirent* no readdir().
    Repito a operação dir = readdir(diretorio); em um loop imprimindo cada arquivo nele (exceto ".. - dir pai" e ". - o diretorio em si")
    (caso conste menos funcionalidades que o desejado a explicação é só uma: cansaço de correr atrás)

cp:
  Verifico se o arquivo existe. Se sim, abro ele e obtenho seu id (um int). Passo ele para a função tamanho_arqv() recebendo um off_t (inteiro de 64bits)
  como tamnho do arquivo em bytes. Aloco espaço para armazenar o conteudo do arquivo e passo tanto ele, como o id e tamnho na função read().
  Assim tenho o conteudo lido.
  Em seguida eu repito o procedimento de abrir o arquivo de destino, porém apenas "jogo" o conteudo do outro nele.
  Doou close() em ambos os arquivos e libero a memora alocada.
    trecho:
      char* conteudo_origem = new char[tamanho_origem];
      ssize_t conteudo_lido = read(id_origem, conteudo_origem, tamanho_origem);

      ssize_t id_gravado = write(id_destino, conteudo_origem, conteudo_lido);

rm:
    Após garantir que o arquivo existe, eu uso a função unlink() que remove o arquivo; caso esteja aberto 
    ele aguarda até o momento em que o arquivo for fechado. 
    trecho:
      int remove_arquivo = unlink(argv[1]); // o caminho é passado para a função unlink()

mv:
    u simplesmente crio um novo arquivo, contendo os dados do anterior e deleto este.
    Tanto ele muda de diretorio assim, como de nome. Utilizei a biblioteca filesystem e suas funções copy() e remove()
    trecho:
        std::filesystem::copy(argv[1], argv[2]);
        std::filesystem::remove(argv[1]);
    Houve problema ao mudar um diretorio de lugar. Algumas vezes ele simplesmente não aparecia no destino. Acredito em um problema
    de permissão. Procurei passar todas as permissões para arquivo, prevendo algum erro ao manipular ele novamente depois de criado.

cat:
    Aproveitando a ideia do cp, eu abro o arquivo (pegando tamnho, conteudo etc) e imprimo ele em um laço simples.
    O limite de interação sera o tamanho do arquivo em bytes.
    trecho:
          char* conteudo_origem = new char[tamanho_origem];
          ssize_t conteudo_lido = read(id_origem, conteudo_origem, tamanho_origem);
          for(off_t i = 0; i < tam; i++) //imprimo no terminal o conteudo
            cout << cont[i]; 
    Depois fecho o arquivo e libero a memoria alocada.

mkdir:
    Garanto que não exista um diretorio de mesmo nome no destino, nem que o parametro passado seja um arquivo existente.
    Depois é só usar a função mkdir() da biblioteca <unistd.h>
    trecho:
          int criou_dir = mkdir(argv[1], S_IRWXU | S_IRWXO | S_IRWXG);
          Essas são as permissões passadas para o diretorio criado:
          S_IRWXU: Permissões de leitura, escrita e execução para o dono do arquivo (usuário).
          S_IRWXG: Permissões de leitura, escrita e execução para o grupo do arquivo.
          S_IRWXO: Permissões de leitura, escrita e execução para outros (usuários não proprietários e não pertencentes 
          ao grupo).

rmdir:
    Parecido com o mkdir, porém eu uso a função rmdir() da biblioteca <unistd.h>.
    trecho:
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
      Desse jeito eu consigo remover vários diretorios e imprimir os erros possíveis no terminal também.


chmod e chown não foram implementados!


