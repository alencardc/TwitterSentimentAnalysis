#include "dictionary.h"
#include <cmath>
#define SEED 137

int Dictionary::hash (std::string key){
    int hashValue = 0;

    for(int i = 0; i < key.size(); i++){
        hashValue = (hashValue * SEED) + key[i];
    }

    return hashValue % dictionarySize;

}

void Dictionary::setSize(int newSize){
    dictionarySize = newSize;
}
