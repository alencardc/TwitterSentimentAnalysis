#include <vector>
#include <iostream>
#include <string>

typedef struct wordData{
    int weight;
    int ocurrences;
    int score;
}wordData;

class Dictionary{
private:
    int dictionarySize;
    std::vector<wordData> registers;


private:
    int hash(std::string key);
    void setSize(int newSize);
    void resizeDictionary();

public:
    void insertWord(wordData newWord);
    void removeWord(wordData toRemove);

};

