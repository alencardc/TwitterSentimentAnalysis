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
#include "Rtrie.h"

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
Tweet readTweet(std::ifstream &file,std::ofstream &tweetsArchive);

//Create a tweet struct of a given CSV string format
Tweet createTweet(std::string line, std::ofstream &tweetsArchive);

//Insert all words of a CSV in the dictionary
bool loadIndexCSV(Dictionary &dictionary, Nodo **trie, std::string fileName);

//Insert words of a given tweet
void insertTweet(Dictionary &dictionary, Nodo **trie, Tweet tweet, std::streampos tweetOffset);

//Create wordData struct
wordData createWord(std::string word, int polarity);

std::string utf8Lowercase(std::string text);

//Classify a given tweet based on the words contained in it
void classifyTweets(std::string fileName, Dictionary dictionary, std::string destino);

//Returns a vector containing the words in the given tweet.
std::vector <utf8_string> splitTweet(Tweet toSplit);

//Fetch a tweet from the file of tweets to be previewed
Tweet fetchTweet(std::ifstream &file);

//Funcao que vai checar se o arquivo UTF8 possui BOM no inicio, caso tenha, posiciona
//ponteiro no bytes seguinte ao
void boomTheBOM(std::ifstream &file);

void imprimeMenu();

void printDerivativeWords(std::vector<std::string> wordsWith);




