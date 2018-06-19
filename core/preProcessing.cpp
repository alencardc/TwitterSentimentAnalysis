#include "preProcessing.h"

utf8_string cleanTweet(utf8_string toClean){
    std::vector <char> pontuacao = {'~', '-', ';', ')', '^', '=', '+', ']', '.', '/', '#' , '@', '*', '$', 'º'};

    int indice, i = 0;

    do{

        while((indice = toClean.find(pontuacao[i])) != utf8_string::npos){
            toClean.erase(indice);
        }
        i++;

    }while(i < pontuacao.size());

    return toClean;
}

Tweet createTweet(std::string line) {
    std::istringstream lineStream(line);
    std::string temp;
    Tweet newTweet;

    getline(lineStream, temp, ',');
    newTweet.text = temp;
    getline(lineStream, temp, ',');
    newTweet.polarity = std::stoi(temp);

    return newTweet;
}

Tweet readTweet(std::ifstream &file) {
    std::string line;

    std::getline(file,line);

    return createTweet(line);
}
