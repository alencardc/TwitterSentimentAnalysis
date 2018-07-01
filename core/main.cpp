#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    int opcao;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;
    std::vector<std::string> wordsWith;
    std::string fileName;
    std::string prefixo;
    int dummy;
    Nodo *trie = NULL;
    Nodo *buscado = NULL;


    while(opcao != 0){
        wordsWith.clear();
        imprimeMenu();
        std::cin >> opcao;

        switch(opcao){
            case 1: std::cout << std::endl << "Nome do arquivo a atualizar dicionario:";
                    std::cin >> fileName;
                    loadIndexCSV(dictionary,&trie,fileName);
                    system("pause");
                    break;
            case 2: std::cout << std::endl << "Nome do arquivo a ser classificado:";
                    std::cin >> fileName;
                    classifyTweets(fileName,dictionary);
                    system("pause");
                    break;
            case 3: std::cout << std::endl << "Prefixo:";
                    std::cin >> prefixo;
                    wordsWith = searchPrefix(trie,prefixo);
                    printDerivativeWords(wordsWith);
                    system("pause");
                    break;
            case 4: std::cout << "Insira a palavra buscada:";
                    std::cin >> prefixo;
                    searchForWord(prefixo,trie);
                    system("pause");
                    break;


        }

    }



	return 0;
}
