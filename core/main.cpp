#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;

    Nodo *trie = NULL;

    loadIndexCSV(dictionary, &trie,"pt.csv");

    std::cout << contemTrie(trie, "carlosdlucka");

    classifyTweets("input.csv", dictionary);

	return 0;
}
