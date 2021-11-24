#include <iostream>
#include <fstream>
#include "TweetManager.h"

TweetManager::TweetManager(char * training, char * testing, char * sentiment, char * output) {
    trainingDataFile = DSString(training);
    testingDataFile = DSString(testing);
    sentimentDataFile = DSString(sentiment);
    outputFile = DSString(output);
}

void TweetManager::getUselessWords() {
    std::ifstream input("uselessWords.txt");
    char buffer[200];
    //populate a dictionary for some words that do not hold any meaning for positive or negative
    while(input.getline(buffer, 200, '\n'))
        uselessWords[buffer] = 1;
}

void TweetManager::parseTrainingFile() {
    std::cout << "PARSING THE TRAINING FILE FOR TWEETS..." << std::endl;

    std::ifstream input(trainingDataFile.c_str());

    std::map<DSString, int>::iterator uselessWordItr;
    char buffer[600];
    char sentiment[2];
    char tweet[600];

    char character[2];
    character[1] = '\0';

    input.getline(buffer, 1000, '\n'); //removing first line of file

    //getting the sentiment and tweet from the input file
    while(!input.eof()) {
        input.getline(sentiment, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, '\n');

        bool end = false;
        DSString word;
        //parsing through the tweet for words and vettng those for only important words
        for(char c : tweet) {
            if(!end) {
                //if the current char is a space, then detect a word
                if(isspace(c) || c == '\0') {
                    uselessWordItr = uselessWords.find(word);
                    //only classify the word if 3 letters or more and not a useless word
                    if(word.getLength() > 2 && uselessWordItr == uselessWords.end()) {
                        classifyWord(word, std::atoi(sentiment));
                    }
                    word = "";
                    if(c == '\0')
                        end = true;
                }
                else {
                    //when preparing words, get rid of numbers, and make everything lowercase
                    if(isalpha(c)) {
                        c = tolower(c);
                        character[0] = c;
                        word += character;
                    }}}}}
    std::cout << "DICTIONARY CREATED." << std::endl << std::endl;
}

void TweetManager::classifyWord(const DSString& word, int sentiment) {
    //fixing the sentiment for the words
    if(sentiment == 0)
        sentiment = -1;
    else
        sentiment = 1;

    //iterating over the dictionary to see if the word is already classified
    std::map<DSString, int>::iterator itr;
    itr = dictionary.find(word);

    //if it is not, then add the word
    if(itr == dictionary.end()) {
        std::cout << "Word " << word << " was not found, adding... " << std::endl;
        dictionary[word] = sentiment;
    }
    //if it is, then adjust the value
    else
        dictionary[word] += sentiment;
}

void TweetManager::parseTestingFile() {
    std::cout << std::endl << "PARSING TESTING FILE FOR TWEETS..." << std::endl;
    char buffer[600];
    char character[2];
    character[1] = '\0';
    //this is parse through the tweets in the testing file
    std::ifstream input(testingDataFile.c_str());

    input.getline(buffer, 1000, '\n'); //removing first line of file

    //getting the sentiment and tweet from the input file
    while(!input.eof()) {

        std::vector<DSString> words(60);
        char id[11];
        char tweet[600];

        input.getline(id, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, ',');
        input.getline(tweet, 1000, '\n');

        bool end = false;
        DSString word;

        //parsing through the characters in the tweet
        for(char c : tweet) {
            if (!end) {
                //if the current char is a space, then detect a word
                if (isspace(c) || c == '\0') {
                    if (word.getLength() > 2 && word.getLength() < 15)
                        words.push_back(word);
                    word = "";
                    if (c == '\0')
                        end = true;
                } else {
                    //when preparing words, get rid of numbers, and make everything lowercase
                    if (isalpha(c)) {
                        c = tolower(c);
                        character[0] = c;
                        word += character;
                    }}}}
        //send the vector of the words with the ID of the tweet out to be sorted through
        parseTestingTweet(words, id);
        memset(buffer, 0, strlen(buffer));
    }
    std::cout << "TESTING TWEETS SENTIMENTS DETERMINED." << std::endl << std::endl;
}

void TweetManager::parseTestingTweet(std::vector<DSString> tweet, const char *ID) {
    int sentiment = 0;
    std::map<DSString, int>::iterator dictionaryItr;

    //add up the sentiments of the words in the tweet
    for(int i = 0; i < tweet.size(); ++i) {
        dictionaryItr = dictionary.find(tweet.at(i));

        if(dictionaryItr != dictionary.end())
            sentiment += dictionaryItr->second;
    }

    //fix the sentiment to be binary for comparing later & add to the list of determined sentiments
    if(sentiment > 0)
        sentiment = 4;
    else
        sentiment = 0;

    DSString tweetID(ID);
    determinedSentiments[tweetID] = sentiment;

    std::cout << tweetID << " : " << sentiment << std::endl;

    std::cout << "Size of determined sentiments: " << determinedSentiments.size() << std::endl;
}

void TweetManager::parseTestSentiments() {

    std::ifstream input(sentimentDataFile.c_str());

    char buffer[100];
    char sentimentChar[2];
    char id[11];

    input.getline(buffer, 100, '\n');   //removing the first line

    //for each line, extract the sentiment and id of all the given sentiments
    while(!input.eof()) {
        input.getline(sentimentChar, 1000, ',');
        input.getline(id, 1000, '\n');

        //typecast the char * for sentiment to int
        int sentiment = std::atoi(sentimentChar);

        //create a vector of all of the given sentiments
        actualSentiments.emplace_back(std::pair<DSString, int>(DSString(id), sentiment));

        memset(buffer, 0, strlen(buffer));
    }
}

void TweetManager::compareSentiments() {
    std::cout << "COMPARING DETERMINED AND GIVEN SENTIMENTS..." << std::endl << std::endl;
    //creating the iterator for the determined sentiments map
    std::map<DSString, int>::iterator itr;
    correctTweets = 0;
    totalTweets = determinedSentiments.size();

    //for each element in the actual sentiments recorded, find them in the determined sentiments
    for(int i = 0; i < actualSentiments.size(); ++i) {
        itr = determinedSentiments.find(actualSentiments.at(i).first);
        if(itr != determinedSentiments.end()) {
            //compare if the same ID in the two lists has the same sentiment in both
            if(itr->second == actualSentiments.at(i).second)
                ++correctTweets;
            else
                incorrectIDs.push_back(actualSentiments.at(i).first);
        }
    }

    std::cout << "Size of  actual sentiments: " << actualSentiments.size() << std::endl;
    std::cout << "Correctly ID'ed tweets: " << correctTweets << std::endl;
    std::cout << "Incorrect ID'ed tweets list size: " << incorrectIDs.size() << std::endl;

    std::cout << std::endl << "SENTIMENTS HAVE BEEN COMPARED." << std::endl << std::endl;
}

void TweetManager::createOutput() {
    std::cout << "CREATING OUTPUT FILE..." << std::endl << std::endl;
    //opening the file that will contain the results
    std::ofstream output(outputFile.c_str());

    //calculating the percent of tweets correctly IDed
    float percentCorrect = (float)correctTweets / (float) totalTweets;
    percentCorrect = (int)(percentCorrect * 1000 + .5);

    //printing the decimal and incorrect IDs to the output file
    output << (float) percentCorrect / 1000;
    output << std::endl;

    for(int i = 0; i < incorrectIDs.size(); ++i)
        output << incorrectIDs.at(i) << std::endl;

    std::cout << "OUTPUT FILE CREATED." << std::endl;
}