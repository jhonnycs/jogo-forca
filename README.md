# jogo-forca

Jogo da forca feito em C, do livro "Introdução à programação em C:<br>
os primeiros passos de um desenvolvedor", de Maurício Aniche

Em determinado momento, o livro pede melhorias do jogo da forca,<br>
que é feito ao longos dos capítulos.<br>
[aqui](https://github.com/jhonnycs/jogo-forca/blob/main/forca.c), você encontra o jogo antes de ser melhorado.<br>
[aqui](https://github.com/jhonnycs/jogo-forca/blob/main/forca-melhorado.c), você encontra o jogo depois de ser melhorado.

## Funcionamento
O jogo lê o arquivo txt chamado `palavras.txt`, que tem na sua primeira linha a quantidade de palavras<br>
que está guardada e nas linhas seguintes, apenas em maiúsculo, as palavras que podem ser sorteadas.

Durante o jogo, o player poderá escolher a dificuldade e terá algumas chances para adivinhar a palavra<br>
de acordo com o nível escolhido. Se o jogador ganhar, pode adicionar uma nova palavra ao arquivo.

Ao final de cada partida, o jogador poderá adicionar seu nome ao ranking de jogadores, o qual é um arquivo<br>
txt chamado `ranking.txt`, onde a pontuação de cada jogador é calculada de acordo com uma fórmula encontrada na<br>
função `calcPontuacaoPlayer()`.

## Rodando o código

Para rodar o código, você precisa ter um compilador instalado. Recomendo o gcc. Para verificar se o gcc está instalado,<br>
rode `gcc --version` no terminal e deverá aparecer a versão do gcc. Caso não aparece, instale. Caso esteja instalado<br>
e não apareça, procure verificar se ele está na variável PATH do sistema que você está usando.

Tendo o gcc instalado, basta rodar, na mesma pasta onde estão todos os arquivos do jogo:

### No Windows:

```
gcc forca-melhorado.c -o main.exe
./main.exe
```

### No Linux

```
gcc forca-melhorado.c -o main
./main
```
