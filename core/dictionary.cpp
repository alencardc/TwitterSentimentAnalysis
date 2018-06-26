#include "dictionary.h"
#include <stdlib.h>
#include <cmath>

#define SEED 7
#define SEED2 3
#define MAXLENGHT 8
#define TAXAMAXIMA 0.5
#define EXTRASIZE 10
#define INITSIZE 300

//Constructor for dictionary
Dictionary::Dictionary() {
    currentSize = 0;                    //Set the current size to 0 and then resizes the
    setMaxSize(nextPrime(INITSIZE));    //vector to INITSIZE.

}

//Acumulação polinomial
int Dictionary::hash1 (utf8_string key) {
    unsigned int hashValue = 0;

    for(int i = 0; i < key.size() && i < MAXLENGHT; i++) {
        hashValue = (hashValue * SEED) + key.at(i);
    }
    return hashValue % maxSize;

}

int Dictionary::hash2 (utf8_string key) {
    unsigned int hashValue = 0;

    for(int i = 0; i < key.size() && i < MAXLENGHT; i++) {
        hashValue = (hashValue * SEED2) + key.at(i);
    }
    return hashValue % maxSize;
}

//CHanges max size
void Dictionary::setMaxSize(int newSize) {
    maxSize = newSize;
    table.resize(newSize);
}

//Insere uma palavra
int Dictionary::insertWord(wordData newWord) {
    unsigned int key;
    unsigned int firstKey  = hash1(newWord.word);
    unsigned int secondKey = hash2(newWord.word);
    int j;
    /*
    currentSize++;
    //N�o vai ser necess�rio quando fizermos a fun��o de re-hash, basta fazer o teste se é necessario
    //e coloca-la aqui
    if(currentSize > maxSize) {
        setMaxSize(currentSize);
    }
    */
    // Get an empty position in the table
    do {
        key = (firstKey + j * secondKey) % maxSize;
        j++;
    } while (isEmpty(key) == false);

    table[key] = newWord;
    return key;
}
//Retorna uma palavra
wordData Dictionary::retrieveWordData(utf8_string word) {
    int key;
    wordData emptyWord;

    key = find(word);

    if (key == -1)  //If word given isnt in the table return a empty struct
        return emptyWord;

    return table[key];
}

bool Dictionary::isEmpty(unsigned int key) {
    return table[key].word.empty();
}

int Dictionary::find(utf8_string word) {
    unsigned int key;
    unsigned int firstKey  = hash1(word);
    unsigned int secondKey = hash2(word);
    std::string wordBuff;
    std::string wordCopy = word.c_str();
    int j = 0;

    do {    //Calculate key searching for the word
        key = (firstKey + j * secondKey) % maxSize;
        wordBuff = table[key].word.c_str();
        j++; //Now it increments on while statement
    } while ((wordBuff != wordCopy) && (key != firstKey || j-1 == 0));

    if (wordBuff != wordCopy) //word isnt in the dictionary
        return -1;

    return key;
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
s