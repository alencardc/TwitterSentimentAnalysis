#include "preProcessing.h"

utf8_string cleanTweet(std::string toClean){
    std::vector <char> pontuacao = {'~', '-', ';', '"', ')', '^', '=', '+', ']', '.', '/', '#' , '@', '*', '$', 'º', '!', '?', ':', '['};


    int indice, i = 0;

    //Percorre o vetor de pontuação, e procura esses caracteres na string para elimina-los
    do{
        toClean.erase(std::remove(toClean.begin(), toClean.end(), pontuacao[i]), toClean.end());
        /*while((indice = toClean.find(pontuacao[i])) != std::string::npos){
            std::cout << toClean << std::endl;
            std::cout << " i:" << indice << " " << toClean[indice] << std::endl;
            system("pause");
            toClean.erase(indice, indice);
        }*/
        i++;//usado para acessar novo caractere

    }while(i < pontuacao.size());

    return toClean; //Retorna utf8_string limpa
}


//Retorna um vetor de strings(utf8), contendo a blacklist
std::vector<utf8_string> createBlacklist(std::string archiveName) {
    std::ifstream archive;
    std::vector<utf8_string> blackList;

    utf8_string toInsert;   //Usada para ir inserindo as palavras no vetor
    std::string stopWord;   //Usada para ler o arquivo

    archive.open(archiveName);

    if(archive.is_open()) {
        while(getline(archive,stopWord,',')) {   //Le tendo como separador a ','
            toInsert = utf8_string(stopWord);   //Transforma em utf e insere no vetor
            blackList.push_back(toInsert);
            toInsert.clear();
        }
        archive.close();
        return blackList;

    }
}

Tweet createTweet(std::string line) {
    std::istringstream lineStream(line);
    std::string temp;
    Tweet newTweet;

    getline(lineStream, temp, ',');
    newTweet.text = utf8_string(cleanTweet(temp));
    std::cout << newTweet.text.c_str() << std::endl;
    getline(lineStream, temp, ',');
    newTweet.polarity = std::atoi(temp.c_str());

    return newTweet;

}

Tweet readTweet(std::ifstream &file) {
    std::string line;

    std::getline(file,line);

    return createTweet(line);
}

wordData createWord(std::string word, int polarity) {
    wordData newWord;

    newWord.word        = utf8_string(word);
    //Need changes
    newWord.weight      = (float)polarity;  //Weight começa com a polaridade
    newWord.occurrences = 1;                //Número de ocorrências como o padrão
    newWord.score       = polarity;         //Score da palavra começa com a polaridade

    return newWord;
}

void insertTweet(Dictionary &dictionary, Tweet tweet) {
    //transform(frase.begin(), frase.end(), frase.begin(), ::tolower);
    std::string buffWord;
    wordData word;
    std::istringstream tweetStream(tweet.text.c_str());
    while (getline(tweetStream, buffWord, ' ')) {
        word = createWord(buffWord, tweet.polarity);
        dictionary.insertWord(word);
        //std::cout << word.word.c_str() << std::endl;
    }
}

bool CSVtoDictionary(Dictionary &dictionary, std::string fileName) {
    std::string buffTweet;
    Tweet tweet;
    std::ifstream file;
    file.open(fileName);
    int j = 0;
    while (file.eof() == false) {
        tweet = readTweet(file);
        insertTweet(dictionary, tweet);
    }
    return 1;
}
