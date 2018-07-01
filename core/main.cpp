#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;
    std::vector<std::string> wordsWith;

    Nodo *trie = NULL;

    loadIndexCSV(dictionary, &trie,"pt.csv");

    std::cout << contemTrie(trie, "carlosdlucka");

    wordsWith = searchPrefix(trie, "ent");
    for (int i = 0; i < wordsWith.size(); i++)
        std::cout << wordsWith[i] << std::endl;

    classifyTweets("input.csv", dictionary);

	return 0;
}
