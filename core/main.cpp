#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main() {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;



    CSVtoDictionary(dictionary,"pt.csv");


    classifyTweets("input.csv", dictionary);








	return 0;
}
