#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

#define TAMANHO_PALAVRA 20

char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

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
    printf("Chute uma letra:\n> ");
    scanf(" %c", &chute);

    if (letraExiste(chute)) {
        printf("Correto.");
    } else {
        printf("Errou.");
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
    int erros = chutesErrados;

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
    
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

int enforcou() {
    return chutesErrados() >= 5;
}

int ganhou() {
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

void adicionarPalavra() {
    char simOuNao;

    printf("Desejas adicionar uma nova palavra (s ou n)?\n> ");
    scanf(" %c", &simOuNao);

    while (simOuNao != 's' && simOuNao != 'n') {
        printf("Por favor, digite s ou n:\n> ");
        scanf(" %c", &simOuNao);
    }

    if (simOuNao == 's') {
        char novaPalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra:\n> ");
        scanf("%s", novaPalavra);

        FILE* f = fopen("palavras.txt", "r+");
        
        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);
        fclose(f);
    }
    
}

int main() {

    abertura();
    escolhePalavra(palavraSecreta);

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

    adicionarPalavra();
}