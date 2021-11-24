#ifndef TWEETMANAGER_H
#define TWEETMANAGER_H

#include <map>
#include <vector>
#include "DSString.h"

class TweetManager {
private:
    DSString trainingDataFile, testingDataFile, sentimentDataFile, outputFile;

    std::map<DSString, int> dictionary;
    std::map<DSString, int> uselessWords;

    std::map<DSString, int> determinedSentiments;
    std::vector<std::pair<DSString, int>> actualSentiments;

    std::vector<DSString> incorrectIDs;
    int correctTweets, totalTweets;

public:
    TweetManager(char *, char *, char *, char *);
    ~TweetManager() = default;

    void parseTrainingFile();
    void classifyWord(const DSString&, int);

    void getUselessWords();

    void parseTestingFile();
    void parseTestingTweet(std::vector<DSString>, const char *);

    void parseTestSentiments();
    void compareSentiments();

    void createOutput();
};


#endif