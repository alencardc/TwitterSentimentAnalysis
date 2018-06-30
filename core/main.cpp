#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;

    Nodo *trie;

    loadIndexCSV(dictionary, trie,"pt.csv");


    classifyTweets("input.csv", dictionary);

	return 0;
}
