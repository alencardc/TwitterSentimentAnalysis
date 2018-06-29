#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main () {
    Dictionary dictionary;
    wordData word;
    Tweet tweet;
    std::vector<utf8_string> words;
    std::vector <wordData> temp;
    std::ifstream file;


    CSVtoDictionary(dictionary,"pt.csv");

    file.open("pt.csv");


    for(int i = 0; i < 20; i++){
        tweet = readTweet(file);
        std::cout <<  "Old polarity:" << tweet.polarity;
        std::cout <<"|| New polarity: " <<classifyTweet(tweet,dictionary) << std::endl;
    }





    file.close();

	return 0;
}
