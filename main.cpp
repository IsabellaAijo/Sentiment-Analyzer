#include "TweetManager.h"

int main( int argc, char*argv[]) {   //argc: argument count argv: argument vector array of required files

    std::cout << "Input files:" << std::endl;
    for(int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;
    std::cout << std::endl;

    //tweet manager oversees the frequency list creation and use
    TweetManager mgr(argv[1], argv[2], argv[3], argv[4]);

    mgr.getUselessWords();
    mgr.parseTrainingFile();
    mgr.parseTestingFile();
    mgr.parseTestSentiments();
    mgr.compareSentiments();
    mgr.createOutput();

    return 0;
}