#include <iostream>
#include <fstream>
#include "preProcessing.h"



int main () {

    Dictionary dictionary;
    wordData word;

    CSVtoDictionary(dictionary, "pt.csv");

	return 0;
}
