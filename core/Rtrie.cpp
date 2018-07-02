#include "Rtrie.h"
#include <iostream>

Nodo* inicializarTrie(void) {
    int i;
    Nodo *nNodo = new Nodo;

    nNodo->isWord = false;

    for (i = 0; i < R_MAX; i++) //Inicializa todos filhos em NULL
        nNodo->prox[i] = NULL;

    return nNodo;
}

Nodo* inserirTrie(Nodo *raiz, std::string chave, std::streampos endTweet) {
    return inserirTrie(raiz, chave, endTweet, 0);
}

Nodo* inserirTrie(Nodo *a, std::string chave, std::streampos endTweet, int d) {

    if (a == NULL)      //Caso o nodo de determinado caractere n tenha sido inicializado
        a = inicializarTrie();

    if (d == chave.size()) {    // Fim da palavra, insere o ponteiro no vetor e marca como palavra existente
        a->endTweets.push_back(endTweet);
        a->isWord = true;
        return a;
    }

    int c = (unsigned char)chave.at(d);
    a->prox[c] = inserirTrie(a->prox[c], chave, endTweet, d+1); //Insere proximo caractere
    return a;
}

bool contemTrie(Nodo *raiz, std::string chave) {
    return (buscarTrie(raiz, chave).size() > 0); // Para esse caso, o campo valor eh  numero de vezes que a palavra foi inserida, logo se for 0, nunca foi inserido
}

std::vector<std::streampos> buscarTrie(Nodo *raiz, std::string chave) {
    Nodo *a = new Nodo;
    std::vector <std::streampos> empty;

    a = buscarTrie(raiz, chave, 0); //Busca o nodo na arvore
    if (a == NULL)  //Caso n exista retorna vetor vazio
        return empty;   
    return a->endTweets;    //Retorna vetor de ponteiro para os tweets
}

Nodo *buscarTrie(Nodo *a, std::string chave, int d) {
    if (a == NULL)  //Palavra nao esta presente
        return NULL;
    if (d == chave.size())  //Encontrou a palavra
        return a;
    int c = (unsigned char)chave.at(d);     
    return buscarTrie(a->prox[c], chave, d+1);  //Busca no nodo referente ao proximo caractere da chave
}


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


std::vector<std::string> searchPrefix(Nodo *raiz, std::string &prefix) {
    std::vector<std::string> wordList;
    int i = 0;
    std::string palavra;

    //Percorre a trie ate o fim do prefixo
    while (i < prefix.size() && raiz->prox[prefix[i]] != NULL) {
        raiz = raiz->prox[prefix[i]];
        i++;
    }

    //Caso prefixo n exista retorna vetor vazio
    if(i < prefix.size()){
        return wordList;
    }

    //Busca todas palavras com o prefixo e retorna a lista gerada
    getStartWith(prefix, raiz, wordList);
    return wordList;
}



void searchForWord(std::string word, Nodo *trie){
    std::vector <std::streampos> buscado;
    std::ifstream tweetsArchive;
    std::ofstream destino;
    std::string tweet;
    tweetsArchive.open("tweets.csv");


    buscado = buscarTrie(trie, word);
    word.append(".csv");
    destino.open(word);


    if(buscado.size() > 0){     //Percorrer toda lista de ponteiros de tweets
        for(int i = 0; i < buscado.size(); i++){ 
            tweetsArchive.seekg(buscado[i]); //Vai ate a posicao do tweet
            getline(tweetsArchive,tweet);   // Le o tweet
            destino << tweet;
            destino << "\n";
        }

        std::cout << "Tweets registrados em " << word << std::endl;
        destino.close();
        tweetsArchive.close();

    }

    else{
        std::cout << "Palavra n? encontrada na trie.";
        destino.close();
        tweetsArchive.close();
    }

}



