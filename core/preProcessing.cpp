#include "preProcessing.h"

utf8_string cleanTweet(utf8_string toClean){
    std::vector <char> pontuacao = {'~', '-', ';', ')', '^', '=', '+', ']', '.', '/', '#' , '@', '*', '$', 'º'};


    int indice, i = 0;

    do{

        while((indice = toClean.find(pontuacao[i])) != utf8_string::npos){
            toClean.erase(indice);
        }
        i++;

    }while(i < pontuacao.size());

    return toClean;
}
