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


    CSVtoDictionary(dictionary, "pt.csv");

    word = dictionary.retrieveWordData("hoje");

    std::cout << std::endl;

    std::cout << "Ocurrences: " << word.occurrences <<std::endl;
    std::cout << "Score: " << word.score << std::endl;
    std::cout << "Weight: " << word.weight << std::endl;

	return 0;
}
