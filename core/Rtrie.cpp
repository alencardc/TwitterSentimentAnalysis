#include "Rtrie.h"

Nodo* inicializarTrie(void) {
    int i;
    Nodo *nNodo = new Nodo;

    nNodo->isWord = false;

    for (i = 0; i < R_MAX; i++)
        nNodo->prox[i] = NULL;

    return nNodo;
}

Nodo* inserirTrie(Nodo *raiz, std::string chave, std::streampos endTweet) {
    return inserirTrie(raiz, chave, endTweet, 0);
}

Nodo* inserirTrie(Nodo *a, std::string chave, std::streampos endTweet, int d) {

    if (a == NULL)
        a = inicializarTrie();

    if (d == chave.size()) {
        a->endTweets.push_back(endTweet);
        a->isWord = true;
        return a;
    }

    int c = (unsigned char)chave.at(d);
    a->prox[c] = inserirTrie(a->prox[c], chave, endTweet, d+1);
    return a;
}

bool contemTrie(Nodo *raiz, std::string chave) {
    return (buscarTrie(raiz, chave).size() > 0); // Para esse caso, o campo valor eh  numero de vezes que a palavra foi inserida, logo se for 0, nunca foi inserido
}

std::vector<std::streampos> buscarTrie(Nodo *raiz, std::string chave) {
    Nodo *a = new Nodo;
    std::vector <std::streampos> empty;
    a = buscarTrie(raiz, chave, 0);
    if (a == NULL)
        return empty; // Para esse caso, o campo valor eh  numero de vezes que a palavra foi inserida, logo se for 0, nunca foi inserido
    return a->endTweets;
}

Nodo *buscarTrie(Nodo *a, std::string chave, int d) {
    if (a == NULL)
        return NULL;
    if (d == chave.size())
        return a;
    int c = (unsigned char)chave.at(d);
    return buscarTrie(a->prox[c], chave, d+1);
}
/*
void todasPalavrasTrie(Nodo *a, std::string& palavra) {
    char proxChar;
    Nodo *filho;

    if (a->isWord) //eh palavra
        std::cout << palavra << "," << a->valor << "\n";

    for (int i = 0; i < R_MAX; i++) {
        proxChar = OFFSET_A + i;
        filho = a->prox[i];
        if (filho) {
            palavra.push_back(proxChar);    //coloca caractere atual na string
            todasPalavrasTrie(filho, palavra);
            palavra.pop_back();             //retira o caractere colocado
        }
    }
}
*/
void getStartWith(std::string& prefix, Nodo *a, std::vector<std::string>& wordList) {
    char proxChar;
    Nodo *filho;
    //Prefix contem, inicialmente, o prefixo procurado, o restante da palavra eh acumulado
    if (a->isWord) //eh palavra
        wordList.push_back(prefix);

    for (int i = 0; i < R_MAX; i++) {
        proxChar = i;
        filho = a->prox[i];
        if (filho) {
            prefix.push_back(proxChar);    //coloca caractere atual na string
            getStartWith(prefix, filho, wordList);
            prefix.pop_back();             //retira o caractere colocado
        }
    }
}
/*
void salvarTrieCSV(Nodo *a) {
    std::string buffPalavra;
    std::ofstream arq;
    arq.open("saida.csv", std::ios::trunc);
    salvarTrieCSV(a, buffPalavra, arq);
    arq.close();
}
/*
void salvarTrieCSV(Nodo *a, std::string& palavra, std::ofstream &arq) {
    char proxChar;
    Nodo *filho;

    if (a->isWord) //eh palavra


    for (int i = 0; i < R_MAX; i++) {
        proxChar = OFFSET_A + i;
        filho = a->prox[i];
        if (filho) {
            palavra.push_back(proxChar);    //coloca caractere atual na string
            salvarTrieCSV(filho, palavra, arq);
            palavra.pop_back();             //retira o caractere colocado
        }
    }
}
*/
std::vector<std::string> searchPrefix(Nodo *raiz, std::string prefix) {
    std::vector<std::string> wordList;
    int i = 0;
    std::string palavra;
    while (i < prefix.size() && raiz->prox[prefix[i]] != NULL) {
        raiz = raiz->prox[prefix[i]];
        i++;
    }

    getStartWith(prefix, raiz, wordList);
    return wordList;
}


