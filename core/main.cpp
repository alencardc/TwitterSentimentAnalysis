#include <iostream>
#include <fstream>
#include "dictionary.h"




int main () {

    Dictionary dictionary;
    wordData word;

    dictionary.CSVtoDictionary("pt.csv");

	return 0;
}
