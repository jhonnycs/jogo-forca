#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

/*
    Melhorias a serem feitas no jogo, todas tiradas do próprio livro:
    Marcarei as melhorias já feitas com um -------------------------- abaixo

    1) Não permitir que o usuário digite nada além de letras maiúsculas. Dica:
        Imprima a letra ‘A’ e a letra ‘Z’ como inteiros (usando %d) e descubra seus
        números. Em seguida, faça um if proibindo o caractere digitado de ser fora
        desse intervalo.
        --------------------------

    2) Não permitir que o usuário insira uma palavra que já exista no arquivo de
        palavras.
        --------------------------

    3) Só possibilitar a inserção de uma nova palavra caso o jogador ganhe o jogo.
    --------------------------

    4) Pergunte ao usuário o nível de dificuldade que ele quer jogar. De acordo
        com o nível, você tem mais ou menos chutes.
        --------------------------

    5) A função enforcou() tem código repetido. Você pode fazer uso da função jachutou() e diminuir a duplicação de código.


    6) Você deve ter reparado que, ao adicionarmos a décima palavra, teremos
        um problema. Isso porque sempre escrevemos em cima do que já está no
        arquivo. E como “10” é maior do que “9”, temos um byte a mais, e o arquivo
        fica desposicionado (o enter some). Para resolver esse problema, combine
        que o número será sempre escrito com 4 algarismos (0001, 0009, 0021,
        e assim por diante). Assim, garantimos que nosso programa funcionará
        bem para até 9999 palavras. Para que isso funcione no printf, passamos
        "%04d" como máscara. Faça essa alteração no jogo.
        --------------------------

    7) Ao final do jogo, pergunte o nome do usuário e salve-o em um arquivo
        ranking.txt, junto com a sua pontuação.
        --------------------------

*/

#define TAMANHO_PALAVRA 20
#define DIFICULDADE_FACIL 6
#define DIFICULDADE_MEDIO 5
#define DIFICULDADE_DIFICIL 4
#define TAM_MAX_NOME_PLAYER 30

char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;
int chutesIncorretos;
int dificuldade;

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void escolhePalavra() {
    FILE* f = fopen("palavras.txt", "r");

    if (!f) {
        printf("Arquivo de palavras não encontrado.\n");
        exit(1);
    }

    int qPalavras;
    fscanf(f, "%d", &qPalavras);

    srand(time(0));
    int randomico = rand() % qPalavras;

    for (int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavraSecreta);
    }
    fclose(f);
}

void chuta() {
    char chute;
    printf("Chute uma letra maiúscula:\n> ");
    scanf(" %c", &chute);

    while (chute < 65 || chute > 90) {
        printf("Por favor, chute uma letra válida (maiúscula):\n> ");
        scanf(" %c", &chute);
    }

    if (letraExiste(chute)) {
        printf("Correto.\n\n");
    } else {
        printf("Errou.\n\n");
        chutesIncorretos++;
    }
    
    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaForca() {
    int erros = chutesErrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n");
    
    printf("Você já deu %d chutes\n", chutesDados);

    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(jaChutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");

}

int letraExiste(char letra) {
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (letra == palavraSecreta[i]) {
            return 1;
        }
    }
    return 0;
}

int chutesErrados() {
    int erros = 0;
    for (int i = 0; i < chutesDados; i++) {
        if (!letraExiste(chutes[i])) erros++;
    }
    return erros;
}

// melhoria 4 --------------------------
void escolhaDificuldade() {
    printf("Escolha a dificuldade:\n");
    printf("(1) Fácil   (2) Médio   (3) Difícil\n> ");
    scanf("%d", &dificuldade);
}

int defineDificuldade() {
    switch (dificuldade) {
    case 1:
        return DIFICULDADE_FACIL;
    case 2:
        return DIFICULDADE_MEDIO;
    case 3:
        return DIFICULDADE_DIFICIL;
    default:
        return DIFICULDADE_MEDIO;
    }
}

int enforcou() {
    return chutesErrados() >= defineDificuldade();
}

int ganhou() {
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

// melhoria 2 --------------------------
int verificarPalavrasIguais(char* palavra1, char* palavra2) {
    int saoIguais = 1;
    if (strlen(palavra1) == strlen(palavra2)) {
        for (int i = 0; i < strlen(palavra1); i++) {
            if (palavra1[i] != palavra2[i]) {
                saoIguais = 0;
                break;
            }
        }
    } else {
        saoIguais = 0;
    }
    return saoIguais;
}

int palavraJaExiste(FILE* f, char* novaPalavra, int qtdPalavras) {
    char palavraDoArquivo[TAMANHO_PALAVRA];

    for (int i = 0; i < qtdPalavras; i++) {
        fscanf(f, "%s", palavraDoArquivo);
        if (verificarPalavrasIguais(novaPalavra, palavraDoArquivo)) {
            return 1;
        }
    }
    return 0;
}

void adicionarPalavra() {
    char simOuNao;

    printf("Desejas adicionar uma nova palavra (S ou N)?\n> ");
    scanf(" %c", &simOuNao);

    while (simOuNao != 's' && simOuNao != 'n' && simOuNao != 'S' && simOuNao != 'N') {
        printf("Por favor, digite S ou N:\n> ");
        scanf(" %c", &simOuNao);
    }

    if (simOuNao == 's' || simOuNao == 'S') {
        char novaPalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra:\n> ");
        scanf("%s", novaPalavra);

        FILE* f = fopen("palavras.txt", "r+");
        
        int qtd;
        fscanf(f, "%d", &qtd);

        if (palavraJaExiste(f, novaPalavra, qtd)) {
            printf("A palavra já existe. Palavra não adicionada\n");
            fclose(f);
        } else {
            qtd++;
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%04d", qtd);
            fseek(f, 0, SEEK_END);
            fprintf(f, "\n%s", novaPalavra);
            printf("Palavra adicionada!\n");
            fclose(f);
        }
    }
}

// melhoria 7 --------------------------
int calcPontuacaoPlayer() {
    int pontuacao;
    pontuacao = (10 - chutesIncorretos) * dificuldade;
    printf("%d\n\n", chutesIncorretos);
    printf("%d\n\n", dificuldade);
    printf("%d\n\n", pontuacao);

    return pontuacao;
}

void insertPlayerRanking() {
    int pontuacao = calcPontuacaoPlayer();
    char nomePlayer[TAM_MAX_NOME_PLAYER];

    printf("Por favor, digite seu nome para inserirmos no ranking:\n> ");
    scanf("%s", nomePlayer);

    FILE* f = fopen("ranking.txt", "a");

    fprintf(f, "%s", nomePlayer);
    for (int i = 0; i < TAM_MAX_NOME_PLAYER - strlen(nomePlayer); i++) {
        fprintf(f, "%c", '.');
    }
    fprintf(f, "%03d", pontuacao);
    fprintf(f, "%c", '\n');
    fclose(f);
}

int main() {
    abertura();
    escolhePalavra(palavraSecreta);
    escolhaDificuldade();

    do {
        desenhaForca();

        chuta();

    } while (!ganhou() && !enforcou());

    if (ganhou()) {
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

        adicionarPalavra();
    } else {
        printf("\nInfelizmente, você foi enforcado\n\n");

        printf("A palavra era **%s**\n\n", palavraSecreta);
 
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    insertPlayerRanking();
}