#include <iostream>
#include "game.h"
#include "console-utils.h"
#include <stdexcept>
#include <limits>


int main(int argc, const char * argv[]){
    if(argc != 2){
        std::cout << "Please run this program with exactly 1 argument: the name of the word list file" << std::endl;
        std::cin.get();
        return 0;
    }
    try{
        std::cout << "Welcome to Evil Hangman! Loading word list..." << std::endl;
        EvilHangmanGame game{argv[1]};

        auto lengths = game.getLengths();
        size_t minLength = (*(lengths.begin())).first;
        size_t maxLength = (*(lengths.rbegin())).first;

        std::cout << "Word list loaded. There are..." << std::endl;
        for(auto & item : lengths)
            std::cout << item.second << " word" << opt_plural(item.second) << " of " << item.first << " character" << opt_plural(item.first) << std::endl;

        std::cout << "Choose a word length to play at" << std::endl;
        size_t lengthSelection = get_pos_int(minLength, maxLength);
        game.setWordLength(lengthSelection);

        size_t tries = 0;

        while(! game.finished()){
            game.printState();
            std::cout << "Make your next guess." << std::endl;
            char nextGuess = get_single_char();
            game.makeGuess(nextGuess);
            tries ++;
        }

        game.printState();

        std::cout << "Congratulations! You have guessed the word in " << tries << " tries. Press ENTER to EXIT. Because logic.";
        std::cin.get();

    }
    catch(std::runtime_error & e){
        std::cout << "RUNTIME ERROR: " << e.what() << std::endl;
    }
    return 0;
}
