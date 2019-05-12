#ifndef EVILHANGMAN_GAME_H
#define EVILHANGMAN_GAME_H

#include <list>
#include <map>
#include <vector>
#include <set>
#include <iostream>

class EvilHangmanGame{
private:
    std::list<std::string> wordList;
    std::set<char> noMatchGuesses;
    std::string currentlyKnown;
public:
    explicit EvilHangmanGame(const char * fileName);    // argv[]-ből jön a név, felesleges std::string-et csinálni
    size_t remainingWordCount() const noexcept;
    std::map<size_t,size_t> getLengths() const; //kulcs: szóhossz, érték: előfordulások száma
    void setWordLength(unsigned length);
    void makeGuess(char guess, std::ostream & os = std::cout);
    void printState(std::ostream & os = std::cout);
    bool finished() const noexcept;
private:    //segédfüggvények
    static std::vector<bool> makeMatch(const std::string & word, char letter);
    static bool isMatch(const std::string & word, const std::vector<bool> & match, char c) noexcept;
    static bool isZeroMatch(std::vector<bool> match) noexcept;
    bool alreadyGuessed(char guess) const noexcept;
    void addToCurrentlyKnown(std::vector<bool> match, char c);
    std::map<std::vector<bool>,size_t> getMatches(char c) const;
};
#endif
