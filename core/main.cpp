#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main () {

    Dictionary dictionary;
    wordData word;
    Tweet tweet;

    std::ifstream arq;
    std::ofstream arq2;
    std::string text;
    arq.open("pt.csv");
    arq2.open("pt2.csv");
    while (getline(arq, text)) {
        tweet = createTweet(text);
        std::cout << tweet.text.c_str();
        arq2 << tweet.text.c_str() << "\n";
        //std::cout << cleanTweet(utf8_string(text)).c_str() << std::endl;
    }
    arq.close();
    arq2.close();
    //CSVtoDictionary(dictionary, "pt.csv");

	return 0;
}
