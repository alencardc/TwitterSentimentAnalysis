#include "preProcessing.h"

std::string cleanTweet(std::string toClean){
    //Falta adicionar algumas pontuacoes
    std::vector <unsigned char> pontuacao = {'~', '-', '_', '/', '\\', ';', ':', '"', '\'', '(', ')', '[', ']', '{', '}', '^', '=', '+', '-', '.', '#' , '@', '*', '$', '&', '%', '|', '!', '?'};

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

Tweet createTweet(std::string line, std::ofstream &tweetsArchive){
    std::istringstream lineStream(line);
    std::string temp;
    Tweet newTweet;

    getline(lineStream, temp, ',');
    //temp = utf8Lowercase(cleanTweet(temp));

    //Salva o tweet no arquivo de tweets indexado pela trie
    tweetsArchive << temp;
    tweetsArchive << ";";
    temp = cleanTweet(utf8Lowercase(temp));
    newTweet.text = utf8_string(temp);
    getline(lineStream, temp, ',');
    newTweet.polarity = std::atoi(temp.c_str());

    tweetsArchive << newTweet.polarity << "\n";
    tweetsArchive.flush();
    return newTweet;

}

Tweet readTweet(std::ifstream &file,std::ofstream &tweetsArchive) {
    std::string line;

    std::getline(file,line);

    return createTweet(line, tweetsArchive);
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

void insertTweet(Dictionary &dictionary, Nodo **trie, Tweet tweet, std::streampos tweetOffset) {
    //transform(frase.begin(), frase.end(), frase.begin(), ::tolower);
    std::string buffWord;
    wordData word;
    std::istringstream tweetStream(tweet.text.c_str());

    while (getline(tweetStream, buffWord, ' ')) {
        if(buffWord.size() > 2){
            word = createWord(buffWord, tweet.polarity);

            *trie = inserirTrie(*trie, word.word.c_str(), tweetOffset);

            dictionary.insertWord(word);
        }
    }

}

bool loadIndexCSV(Dictionary &dictionary, Nodo **trie, std::string fileName) {
    std::string buffTweet;
    Tweet tweet;
    std::streampos tweetOffset;
    std::ofstream tweetsArchive;

    std::ifstream file;
    file.open(fileName);
    boomTheBOM(file);

    tweetsArchive.open("tweets.csv", std::ofstream::app);

    if(!file || !tweetsArchive){
        std::cout << "Erro ao abrir arquivo." << std::endl;
        return false;
    }



    int j = 0;

    if (*trie == NULL)
        *trie = inicializarTrie();

    while (file.eof() == false) {
        tweetOffset = tweetsArchive.tellp();
        tweet = readTweet(file,tweetsArchive);
        insertTweet(dictionary, trie, tweet, tweetOffset);
    }

    tweetsArchive.close();
    file.close();
    return true;
}

std::vector <utf8_string> splitTweet(Tweet toSplit){
    std::vector <utf8_string> words;
    std::string buffer;
    std::string wordExtracted;
    buffer = toSplit.text.c_str();

    buffer = utf8Lowercase(buffer);
    buffer = cleanTweet(buffer);

    std::istringstream tweetStream(buffer);

    while (getline(tweetStream, wordExtracted, ' ')) {
        words.push_back(utf8_string(wordExtracted));
    }

    return words;
}

int classifyTweet(Tweet toClassify, Dictionary dictionary){
    std::vector <utf8_string> words;
    wordData dataRetrieved;
    float polarity = 0.0;

    //Divide o tweet em palavras
    words = splitTweet(toClassify);

    //Acumula polaridade das palavras (se não foi encontrada a polaridade é 0.0 e não afeta o calculo).
    for(int i = 0; i < words.size(); i++){
        dataRetrieved = dictionary.retrieveWordData(words[i]);
        polarity += dataRetrieved.weight;
    }

    //Tweet positivo
    if(polarity > 0.1){
        return 1;
    }
    else if(polarity < -0.1){   //Tweet negativo
        return -1;
    }
    else{   //Tweet neutro
        return 0;
    }
}

Tweet fetchTweet(std::ifstream &file){
    Tweet toBePreviewed;
    std::string fetchedTweet;

    //Le arquivo e preenche estrutura tweet com o texto. (a polaridade é preenchida depois).
    getline(file,fetchedTweet);
    toBePreviewed.text = utf8_string(fetchedTweet);

    return toBePreviewed;
}

void classifyTweets(std::string fileName, Dictionary dictionary, std::string destino){
    std::ofstream output;
    std::ifstream input;
    Tweet fetched;

    input.open(fileName);
    output.open(destino);

    //Verifica se input foi aberto
    if(!input.is_open()){
        std::cout << "Falha ao abrir o arquivo de tweets." << std::endl;
        return;
    }
    //Verifica se output foi aberto
    else if (!output.is_open()){
        std::cout << "Falha ao abrir o arquivo de tweets polarizados." << std::endl;
        return;
    }

    //Enquanto não chegou ao fim do arquivo
    while(input.eof() == false){
        fetched = fetchTweet(input);    //Busca tweet e o classifica
        fetched.polarity = classifyTweet(fetched,dictionary);
        //Escreve resultado no arquivo output.csv
        output << fetched.text.c_str() << ";" << fetched.polarity << "\n";

    }

    input.close();
    output.close();

}

//Funcao que vai checar se o arquivo UTF8 possui BOM no inicio, caso tenha, posiciona
//ponteiro no bytes seguinte ao BOM
void boomTheBOM(std::ifstream &file) {
    char a,b,c;
    //Pega os 3 primeiros bytes
    a = file.get();
    b = file.get();
    c = file.get();
    //Verifica se seguem o padrao do BOM, se nao seguir, volta pro inicio do arquivo
    if(a!=(char)0xEF || b!=(char)0xBB || c!=(char)0xBF)
        file.seekg(0);
}

void imprimeMenu(){
    system("cls");
    std::cout << "Opções:" << std::endl;
    std::cout << "1 - Atualiza Dicionário" << std::endl;
    std::cout << "2 - Classifica arquivo de tweets" << std::endl;
    std::cout << "3 - Palavras com determinado prefixo" << std::endl;
    std::cout << "4 - Encontra tweets com determinada palavra" <<std::endl;


}

void printDerivativeWords(std::vector<std::string> wordsWith){
    //Limpa a tela
    system("cls");
    std::cout << "Palavras encontradas:" << std::endl;
    //Se o vetor de palavras está vazio, não foi encontrada nenhuma palavra
    if(wordsWith.size() == 0){
        std::cout << "Não foram encontradas palavras com este prefixo nos tweets." << std::endl;
    }
    //Percorre vetor e imprime as palavras a partir daquele prefixo
    for(int i = 0; i < wordsWith.size(); i++){
        std::cout << i + 1 << "-" << wordsWith[i] << std::endl;
    }

}

