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
} Nodo;

Nodo* inicializarTrie(void);

Nodo* inserirTrie(Nodo *raiz, std::string chave, std::streampos endTweet);
Nodo* inserirTrie(Nodo *a, std::string chave, std::streampos endTweet, int d);

bool contemTrie(Nodo *raiz, std::string chave);

Nodo* buscarTrie(Nodo *raiz, std::string chave, int d);
std::vector<std::streampos> buscarTrie(Nodo *raiz, std::string chave);

void getStartWith(std::string& prefix, Nodo *a, std::vector<std::string>& wordList);

//void todasPalavrasTrie(Nodo *a, std::string& palavra);
//void salvarTrieCSV(Nodo *a);
//void salvarTrieCSV(Nodo *a, std::string& palavra, std::ofstream &arq);

std::vector<std::string> searchPrefix(Nodo *raiz, std::string prefix);

