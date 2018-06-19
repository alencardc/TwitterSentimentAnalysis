#include <vector>
#include <iostream>
#include <string>

typedef struct tweetData{
    int weight;
    int ocurrences;
    int score;
}tweetData;

class Dictionary{
private:
    int dictionarySize;
    std::vector<tweetData> registers;


private:
    int hash(std::string key);
    void setSize(int newSize);
    void resizeDictionary();

public:
    void insertWord(std::string key);
    void removeWord(std::string key);



};
