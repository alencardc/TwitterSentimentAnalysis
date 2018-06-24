#include <iostream>
#include <fstream>
#include "preProcessing.h"
#include "dictionary.h"




int main () {

    Dictionary dictionary;
    wordData word;
    word.word = "alencár";

	std::cout << dictionary.insertWord(word) << std::endl;
	word.word = "é";
	std::cout << dictionary.insertWord(word) << std::endl;
	word.word = "abecederaio";
	std::cout << dictionary.insertWord(word) << std::endl;
	std::cout << dictionary.find(word.word) << std::endl;
	word.word.clear();
	word.word = "jurupinga";
	std::cout << dictionary.insertWord(word) << std::endl;
    std::cout << dictionary.find(word.word) << std::endl;
	return 0;
}
