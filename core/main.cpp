#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    int opcao = 1;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;
    std::vector<std::string> wordsWith; //Guarda todas as palavras presentes no dicionário que começam com determinado prefixo
    std::string fileName;
    std::string prefixo;

    Nodo *trie = NULL;
    //Deleta arquivo de tweets.csv, é gerado pela construção do dicionário.
    remove("tweets.csv");
    loadIndexCSV(dictionary,&trie,"pt.csv");


    //Quando a poção selecionada é 0 o usuario sai do programa
    while(opcao != 0){
        //Limpa o vetor que armazena as palavras retornadas pela pesquisa na trie por um prefixo
        wordsWith.clear();
        imprimeMenu();
        std::cin >> opcao;

        switch(opcao){
                    //Atualiza dicionário
            case 1: std::cout << std::endl << "Nome do arquivo a atualizar dicionario:";
                    std::cin >> fileName;
                    loadIndexCSV(dictionary,&trie,fileName);
                    system("pause");
                    break;

                    //Classifica determinado arquivo de tweets
            case 2: std::cout << std::endl << "Nome do arquivo a ser classificado:";
                    std::cin >> fileName;
                    classifyTweets(fileName,dictionary,"TweetsPolarizados.csv");
                    system("pause");
                    break;

                    //Procura por palavras que contem determinado prefixo
            case 3: std::cout << std::endl << "Prefixo:";
                    std::cin >> prefixo;
                    wordsWith = searchPrefix(trie,prefixo);
                    printDerivativeWords(wordsWith);
                    system("pause");
                    break;
                    
                    //Busca pelos tweets que contem determinada palavra
            case 4: std::cout << "Insira a palavra buscada:";
                    std::cin >> prefixo;
                    searchForWord(prefixo,trie);
                    system("pause");
                    break;


        }

    }



	return 0;
}
