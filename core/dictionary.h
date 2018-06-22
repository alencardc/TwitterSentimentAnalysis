#include <vector>
#include <iostream>
#include "tinyutf8.h"
#include <list>

//Stores the information about the given word
typedef struct wordData{
    utf8_string word;
    int weight;
    int ocurrences; //Number of occurences
    int score;  //Accumulated score
}wordData;

class Dictionary{
private:
    int maxSize = 0;    //Initialization will be altered
    int currentSize = 0;    //Initialization will be altered
    std::vector <wordData> table;   //Table that stores the registers


private:
    //HASH E NÃO HUSH HUSH HUSH(pussycat dools) [Generates the place to where the word belongs]
    int hash(utf8_string key);
    //Change the size of the dictionary (maxsize), will be used in rehash
    void setMaxSize(int newSize);
    //Re-hash funcion
    void resizeDictionary();
    //Returns a bool that indicates if the dictionary needs re-hash or not;
    bool needReHash();

public:
    //Insert wordData
    void insertWord(wordData newWord);
    //Retrieve wordData
    wordData retrieveWordData(utf8_string key);


};
//Endereçamento aberto, linear probing
