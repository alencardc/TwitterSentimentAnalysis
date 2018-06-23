#include "dictionary.h"
#include <stdlib.h>
#include <cmath>
#define SEED 7
#define MAXLENGHT 8

//Acumulação polinomial
int Dictionary::hash (utf8_string key){
    unsigned int hashValue = 0;

    for(int i = 0; i < key.size() && i < MAXLENGHT; i++){
        hashValue = (hashValue * SEED) + key.at(i);
    }
    return hashValue % maxSize;

}

//CHanges max size
void Dictionary::setMaxSize(int newSize){
    maxSize = newSize;
    table.resize(newSize);  //This will be in the rehash function
}

//Insere uma palavra
void Dictionary::insertWord(wordData newWord){
    unsigned int end;

    currentSize++;
    //N�o vai ser necess�rio quando fizermos a fun��o de re-hash, basta fazer o teste se é necessario
    //e coloca-la aqui
    if(currentSize > maxSize){
        setMaxSize(currentSize);
    }

    //Need to verify if the given word is in the table

    end = hash(newWord.word);



    table[end] = newWord;

}
//Retorna uma palavra
wordData Dictionary::retrieveWordData(utf8_string key){
    unsigned int end;

    end = hash(key);

    return table[end];
}

bool Dictionary::needReHash(){
    float ocupacao;

    ocupacao = (float) currentSize / (float) maxSize;

    if(ocupacao < TAXAMAXIMA){
        return false;
    }
    else{
        return true;
    }
}
