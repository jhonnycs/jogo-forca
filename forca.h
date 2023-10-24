// lista de funções que aparecerão no arquivo
// isso é para que o compilador não reclame caso a função
// seja chamada antes de ser declarada
void abertura();
void escolhePalavra();
void chuta();
int jaChutou(char letra);
void desenhaForca();
int letraExiste(char letra);
int chutesErrados();
int enforcou();
int ganhou();
void adicionarPalavra();

void escolhaDificuldade();
int defineDificuldade();

int verificarPalavrasIguais(char* palavra1, char* palavra2);
int palavraJaExiste(FILE* f, char* novaPalavra, int qtdPalavras);

int calcPontuacaoPlayer();
void insertPlayerRanking();