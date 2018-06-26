#include <vector>
#include <iostream>
#include "tinyutf8.h"
#include "preProcessing.h"
#include <list>

//Stores the information about the given word
typedef struct wordData {
    utf8_string word;
    int weight;
    int occurrences; //Number of occurences
    int score;  //Accumulated score

    wordData() :
    word(""), weight(0), occurrences(0), score(0) { }

}wordData;

class Dictionary {
private:
    int maxSize;
    int currentSize;
    std::vector <wordData> table;   //Table that stores the registers

private:
    //HASH E NÃO HUSH HUSH HUSH(pussycat dools) [Generates the place to where the word belongs]
    int hash1(utf8_string key);
    int hash2 (utf8_string key);
    //Change the size of the dictionary (maxsize), will be used in rehash
    void setMaxSize(int newSize);
    //Re-hash funcion
    void resizeDictionary();
    //Returns a bool that indicates if the dictionary needs re-hash or not;
    bool needReHash();
    //Returns true if a given hash key is empty in the table
    bool isEmpty(unsigned int key);

    bool isPrime(int number);

    int nextPrime(int actualN);

public:
    //Default constructor for dictionary
    Dictionary();
    //Insert wordData
    int insertWord(wordData newWord);
    //Retrieve wordData
    wordData retrieveWordData(utf8_string word);
    //Returns hash key for a given word
    int find(utf8_string word);

};
