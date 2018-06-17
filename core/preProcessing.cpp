#define TAMR 10
#include "preProcessing.h"

std::string removePonctuacion(std::string toClean){
    char toRemove[TAMR] = {',', '.', '#', '*', ';', '%', '@','$'};
    int posToRemove;


    //Percorre o vetor de pontua��es a serem removidas
    for(int i = 0; i <TAMR; i++){
        //Enquanto encontrou caracter a ser removido, remove o mesmo da string
        while((posToRemove = toClean.find(toRemove[i])) != -1){
            toClean.erase(posToRemove, 1);
        }
    }

    return toClean;
}
