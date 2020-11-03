# Open MP Word Counter
Grupo: Peter Krause, Samuel Landre

## Sobre
Presente neste diretório encontram-se os arquivos pertencentes à solução do problema de contagem de palavras.
- [Versão Sequencial](word_counter.c)
- [Versão Paralela](word_counter_parallel.c)

O programa varre o famoso poema The Raven, de Edgar Allan Poe. O arquivo [high_hopes](high_hopes.h) contém a letra da música High Hopes, de Pink Floyd, caso o usuário queira testar com outro conjunto de dados.

## Execução
obs.: Foi necessário instalar a versão 7 do GCC para conseguir usufruir do argumento `-fopenmp`.

### Versão Sequencial
Em um terminal qualquer, digite o seguinte trecho para compilar o programa:
```
$ gcc word_counter.c -o <nome_do_output>
```
Para rodá-lo com palavras-chave, digite:
```
$ ./<nome_do_output> tapping napping lenore
```
O número de palavras-chave (`tapping`, `napping`, `lenore`) não possui limites, portanto cabe ao usuário decidir quantas palavras deseja procurar.

### Versão Paralela
Em um terminal qualquer, digite o seguinte trecho para compilar o programa:
```
$ gcc-7 word_counter.c -o <nome_do_output> -pthread
```
Para rodá-lo com palavras-chave, digite:
```
$ ./<nome_do_output> 10 tapping napping lenore
```
O primeiro argumento (`10`) é o número de seções de paralelização desejados, enquanto que todos os argumento subsequentes (`tapping`, `napping`, `lenore`) são as palavras-chave que o usuário deseja procurar.
