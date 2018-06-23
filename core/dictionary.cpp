#include "dictionary.h"
#include <stdlib.h>
#include <cmath>

#define SEED 7
#define MAXLENGHT 8
#define TAXAMAXIMA 0.5
#define EXTRASIZE 10
#define INITSIZE 300

//Constructor for dictionary
Dictionary::Dictionary(){
    currentSize = 0;                    //Set the current size to 0 and then resizes the
    setMaxSize(nextPrime(INITSIZE));    //vector to INITSIZE.

}

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
    table.resize(newSize);
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

bool Dictionary::isPrime(int number){
        for (int div = 2; div < number; div++){
            if (!(number % div)){
                return false;
            }
        }
    return true;
}

int Dictionary::nextPrime(int actualNumber){
    actualNumber++;
    while(!isPrime(actualNumber)){
        actualNumber++;
    }

    return actualNumber;
}

void Dictionary::resizeDictionary(){
    int newSize;

    newSize = nextPrime(maxSize + EXTRASIZE);

    setMaxSize(newSize);
}
