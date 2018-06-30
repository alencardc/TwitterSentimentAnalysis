#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define OFFSET_A 97
#define R_MAX 256 - OFFSET_A

typedef struct sNodo {
    std::vector<unsigned int> endTweets;
    bool isWord;
    struct sNodo *prox[R_MAX-OFFSET_A];
} Nodo;

Nodo* inicializarTrie(void);

Nodo* inserirTrie(Nodo *raiz, std::string chave, unsigned int endTweet);
Nodo* inserirTrie(Nodo *a, std::string chave, unsigned int endTweet, int d);

bool contemTrie(Nodo *raiz, std::string chave);
int buscarTrie(Nodo *raiz, std::string chave);
Nodo *buscarTrie(Nodo *a, std::string chave, int d);

void todasPalavrasTrie(Nodo *a, std::string& palavra);
void salvarTrieCSV(Nodo *a);
void salvarTrieCSV(Nodo *a, std::string& palavra, std::ofstream &arq);

std::vector<std::string> searchPrefix(Nodo *raiz, std::string prefix);

