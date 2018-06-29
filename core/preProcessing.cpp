#include "preProcessing.h"

std::string cleanTweet(std::string toClean){
    //Falta adicionar algumas pontuacoes
    std::vector <unsigned char> pontuacao = {'~', '-', '\'', ';', '"', '(', ')', '^', '=', '+', ']', '.', '/', '#' , '@', '*', '$', '!', '?', ':', '['};

    std::string outputString;
    int indice, i = 0;

    //Percorre o vetor de pontuação, e procura esses caracteres na string para elimina-los
    do{
        while ( (indice = toClean.find(pontuacao[i])) != std::string::npos) {
            toClean.replace(indice, 1, 1, ' ');
        }

        //toClean.erase(std::remove(toClean.begin(), toClean.end(), pontuacao[i]), toClean.end());
        i++;//usado para acessar novo caractere
    }while(i < pontuacao.size());

    //Remover multiplos espacos
    unique_copy (toClean.begin(), toClean.end(), std::back_insert_iterator<std::string>(outputString),
                [](char a,char b){
                    return isspace(a) && isspace(b);
                });

    return outputString; //Retorna utf8_string limpa
}

std::string utf8Lowercase(std::string text) {
    // ISSUE: o char u acentuado esta dando problemas
    for (int i = 0; i < text.size(); i++) {
        if ( (text[i] >= 'A' && text[i]<= 'Z'))
            text[i] = text[i] + 32;
        else if ((unsigned char)text[i]>= UTF_firstUPPER && (unsigned char)text[i]<= UTF_lastUPPER/* && text[i-1] == 195*/)
            text[i] = text[i] + 32;

    }
    return text;
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
    //temp = utf8Lowercase(cleanTweet(temp));
    temp = cleanTweet(utf8Lowercase(temp));
    newTweet.text = utf8_string(temp);
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
