#include "game.h"
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <cctype>

EvilHangmanGame::EvilHangmanGame(const char * fileName) : wordList{}, noMatchGuesses{}, currentlyKnown{""} {
    std::ifstream ifs{fileName};
    if(!ifs.is_open())
        throw std::runtime_error{"Unable to open specified file"};

    std::string line;
    while( ! std::getline(ifs, line).eof() ){
        if(std::find_if(line.begin(), line.end(), [](char c){return !(isalpha(c) || c == '-');}) != line.end())
            throw std::runtime_error{line + ": Invalid input file format - each line must contain a single word (letters or '-' only)"};

        wordList.push_back(line);
    }
}

size_t EvilHangmanGame::remainingWordCount() const noexcept {
    return wordList.size();
}

std::map<size_t,size_t> EvilHangmanGame::getLengths() const {
    std::map<size_t,size_t> result;

    for(auto word : wordList)
        result[word.length()] ++;

    return result;
}

void EvilHangmanGame::setWordLength(unsigned length){
    wordList.remove_if( [length] (std::string arg) {return arg.length() != length;} );
    if(wordList.size() == 0)
        throw std::runtime_error{std::string{"No words of length "} + std::to_string(length) + " available"};
    for(size_t i=0; i<length; i++)
        currentlyKnown.append("_");
}

void EvilHangmanGame::makeGuess(char guess, std::ostream & os){
    if(alreadyGuessed(guess)){
        os << "You already guessed that, dummy!" << std::endl;
        return;
    }
    auto matchMap = getMatches(guess);

    // legtöbb szóra illő minta megkeresése
    using pair_type = decltype(matchMap)::value_type;
    auto comparision = [] (const pair_type & lhs, const pair_type & rhs){
        return lhs.second < rhs.second;
    };
    std::vector<bool> maxMatch = (* (std::max_element(matchMap.begin(), matchMap.end(), comparision))).first;

    // játékállapot frissítése
    if(isZeroMatch(maxMatch))
        noMatchGuesses.insert(guess);
    else
        addToCurrentlyKnown(maxMatch, guess);

    // nem illeszkedő szavak törlése
    auto notMatching = [guess, maxMatch] (const std::string & word) {
        return ! isMatch(word, maxMatch, guess);
    };
    wordList.remove_if(notMatching);
}

void EvilHangmanGame::printState(std::ostream & os){
    os << std::endl << "--- Game State ---" << std::endl << "Possible words: " << remainingWordCount() << std::endl;
    os << "Known letters: " << currentlyKnown << std::endl;
    if(noMatchGuesses.size() > 0){
        os << "Guessed with no matches: ";
        for(char c : noMatchGuesses)
            os << c << ", ";
        os << "\b\b \n";    // utolsó vessző törlése
    }
    os << std::endl;
}

bool EvilHangmanGame::finished() const noexcept {
    if(currentlyKnown.length() == 0)
        return false;
    if(currentlyKnown.find('_') == std::string::npos)
        return true;
    return false;
}

std::vector<bool> EvilHangmanGame::makeMatch(const std::string & word, char letter){
    std::vector<bool> result(word.length());

    auto eval_char = [letter] (char c){
        return (c == letter);
    };

    std::transform(word.begin(), word.end(), result.begin(), eval_char);

    return result;
}

bool EvilHangmanGame::isMatch(const std::string & word, const std::vector<bool> & match, char c) noexcept {

    if(word.length() != match.size())
        return false;

    for(size_t i=0; i< match.size(); i++)
        if( (match[i]) != (word[i] == c) )
            return false;

    return true;
}

std::map<std::vector<bool>,size_t> EvilHangmanGame::getMatches(char c) const {
    std::map<std::vector<bool>,size_t> result;
    for(auto & word : wordList){
        result[makeMatch(word,c)] ++;
    }
    return result;
}

bool EvilHangmanGame::isZeroMatch(std::vector<bool> match) noexcept {
    for(bool bit : match)
        if(bit)
            return false;
    return true;
}

void EvilHangmanGame::addToCurrentlyKnown(std::vector<bool> match, char c){
    if(currentlyKnown.length() != match.size())
        throw std::runtime_error{"currentlyKnown string uninitialized, or wrong length of match pattern used - this should never happen if the code is correct"};
    for(size_t i=0; i<match.size(); i++)
        if(match[i])
            currentlyKnown[i] = c;
}

bool EvilHangmanGame::alreadyGuessed(char guess) const noexcept {
    if(noMatchGuesses.find(guess) != noMatchGuesses.end())
        return true;
    if(currentlyKnown.find(guess) != std::string::npos)
        return true;
    return false;
}
