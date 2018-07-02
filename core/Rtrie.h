#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define OFFSET_A 97
#define R_MAX 256

typedef struct sNodo {
    std::vector<std::streampos> endTweets;
    bool isWord;
    struct sNodo *prox[R_MAX];

    sNodo():
        isWord(false)
    {}
} Nodo;

//Inicializa os nodos da arvore, colocando NULL nos filhos
Nodo* inicializarTrie(void);

//Insere uma palavra e seu endereco dentro do arquivo na trie
Nodo* inserirTrie(Nodo *raiz, std::string chave, std::streampos endTweet);
Nodo* inserirTrie(Nodo *a, std::string chave, std::streampos endTweet, int d);

//Verifica se determinada palavra esta na trie
bool contemTrie(Nodo *raiz, std::string chave);

//Retorna nodo nulo se nao encontrar ou o proprio nodo caso encontre. Funcao utilizada pela contem trie
Nodo* buscarTrie(Nodo *raiz, std::string chave, int d);
//Retorna vetor com ponteiro pra todos tweets que contem a palavra buscada
std::vector<std::streampos> buscarTrie(Nodo *raiz, std::string chave);

//Encontra todas palavras que possuem determinado prefixo
void getStartWith(std::string& prefix, Nodo *a, std::vector<std::string>& wordList);
std::vector<std::string> searchPrefix(Nodo *raiz, std::string &prefix);

//Gera arquivo com tweets de determinada palavra
void searchForWord(std::string word, Nodo *trie);
