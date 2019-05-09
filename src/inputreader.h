#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <map>
#include <fstream>

class WordStore;

class InputReader{
private:
    std::ifstream _ifs; // többször végigmegy a fájlon, ezért tárolja az input streamet
    std::map<size_t,size_t> _wordLengthCounts; // kulcs: szóhossz, érték: ilyen hosszú szavak száma
public:
    explicit InputReader(const char * fileName);  // ide felesleges std::string, argv[1] úgyis const char *
    const map<size_t,size_t> wordLengthCounts; // publikusan csak a map const függvényei hívhatók, így "read-only"
    WordStore MakeWordStore(size_t length);
};

#endif
