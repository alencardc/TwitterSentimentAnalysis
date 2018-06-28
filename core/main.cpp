#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main () {

    Dictionary dictionary;
    wordData word;
    Tweet tweet;

    std::ifstream arq;
    std::string text;
    arq.open("pt.csv");
    while (getline(arq, text)) {
        createTweet(text);
        //std::cout << cleanTweet(utf8_string(text)).c_str() << std::endl;
    }
    arq.close();
    //CSVtoDictionary(dictionary, "pt.csv");

	return 0;
}
