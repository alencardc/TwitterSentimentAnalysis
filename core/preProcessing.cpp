#include "preProcessing.h"

utf8_string cleanTweet(utf8_string toClean){
    std::vector <char> pontuacao = {'~', '-', ';', ')', '^', '=', '+', ']', '.', '/', '#' , '@', '*', '$', 'º'};


    int indice, i = 0;
    //Percorre o vetor de pontuação, e procura esses caracteres na string para elimina-los
    do{

        while((indice = toClean.find(pontuacao[i])) != utf8_string::npos){
            toClean.erase(indice);
        }
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
