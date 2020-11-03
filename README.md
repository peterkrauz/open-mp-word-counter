# Open MP Word Counter
Grupo: Peter Krause, Samuel Landre

## Sobre
Presente neste diretório encontram-se os arquivos pertencentes à solução do problema de contagem de palavras.
- [Versão Sequencial](word_counter.c)
- [Versão Paralela](word_counter_parallel.c)

O programa varre o primeiro capítulo do livro [Tibetano dos Mortos](https://en.wikipedia.org/wiki/Bardo_Thodol), em sua tradução por Evans-Wentz para o inglês, que pode ser encontrada neste link [aqui](https://www.sacred-texts.com/bud/tib/psydead.htm).

## Detalhes da Implementação
O problema foi resolvido da seguinte forma:

### Sequencial
1. Separa o texto em array de linhas (delimitadas por `\n`)
2. Itera por cada linha deste array
3. Para cada palavra-chave, procura por uma correspondência da mesma nesta linha
4. Se houve correspondência, incrementa-se o número de ocorrências da palavra.

### Paralela
1. Separa o texto em array de linhas (delimitadas por `\n`)
2. Cria-se uma seção paralela para cada seção fornecida pelo usuário
3. Cada seção itera por cada linha em um intervalo de linhas
4. Para cada palavra-chave, procura por uma correspondência da mesma nesta linha
5. Se houve correspondência, a thread em questão se apodera do Mutex daquela ocorrência, daí incrementa-se o número de ocorrências da palavra, e então libera o Mutex.


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
$ gcc-7 -fopenmp word_counter.c -o <nome_do_output> -pthread
```
Para rodá-lo com palavras-chave, digite:
```
$ ./<nome_do_output> 10 tapping napping lenore
```
O primeiro argumento (`10`) equivale ao número de seções paralelas desejadas, enquanto que todos os argumento subsequentes (`tapping`, `napping`, `lenore`) são as palavras-chave que o usuário deseja procurar.
