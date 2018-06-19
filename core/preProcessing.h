//Header for the functions used in the preProcessing phase
#include <fstream>
#include<string>
#include <vector>
#include <iostream>
#include <sstream>
#include "tinyutf8.h"


typedef struct sTweet {
    int polarity;
    utf8_string text;
} Tweet;

//Removes the ponctuacion of the given string
utf8_string cleanTweet(utf8_string toClean);

//Read a tweet from a file ( <<< melhora esse comentario pf)
Tweet readTweet(std::ifstream &file);

//Create a tweet struct of a given CSV string format
Tweet createTweet(std::string line);
