//Header for the functions used in the preProcessing phase
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "tinyutf8.h"
#include <sstream>
#include <cstdio>
#include <iterator>
#include "dictionary.h"

#define UTF_firstUPPER 128
#define UTF_lastUPPER 159

typedef struct sTweet {
    int polarity;
    utf8_string text;

} Tweet;


//Removes the ponctuacion of the given string
std::string cleanTweet(std::string toClean);

//Returns a vector containing all the stopwords to be removed from the tweets
std::vector<utf8_string> createBlacklist(std::string archiveName);

//Read a tweet from a file ( <<< melhora esse comentario pf)
Tweet readTweet(std::ifstream &file);

//Create a tweet struct of a given CSV string format
Tweet createTweet(std::string line);

//Insert all words of a CSV in the dictionary
bool CSVtoDictionary (Dictionary &dictionary, std::string fileName);

//Insert words of a given tweet
void insertTweet(Dictionary &dictionary, Tweet tweet);

//Create wordData struct
wordData createWord(std::string word, int polarity);

std::string utf8Lowercase(std::string text);

//Classify a given tweet based on the words contained in it
int classifyTweet(Tweet toClassify, Dictionary dictionary);

//Returns a vector containing the words in the given tweet.
std::vector <utf8_string> splitTweet(Tweet toSplit);

//Fetch a tweet from the file of tweets to be previewed
Tweet fetchTweet(std::ifstream &file);

//Classify the tweets presents in the given filename based on the data presented on dictionary, and then records the result in
//output.csv
void classifyTweets(std::string fileName, Dictionary dictionary);
