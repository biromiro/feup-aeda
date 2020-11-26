#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}


bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.word;
}

bool WordMeaning::operator==(const WordMeaning &rhs) const {
    return word == rhs.word &&
           meaning == rhs.meaning;
}

bool WordMeaning::operator!=(const WordMeaning &rhs) const {
    return !(rhs == *this);
}

void Dictionary::readDictionary(ifstream &f)
{
    std::string word, meaning;
    while(!f.eof()){
        getline(f,word);
        getline(f,meaning);
        words.insert(WordMeaning(word,meaning));
    }
}

string Dictionary::searchFor(string word) const
{
    const WordMeaning wordMeaning("","");
    auto val =  words.find(WordMeaning(word,""));
    if (val == wordMeaning) {
        throw WordInexistent(words,word);
    } else {
        return val.getMeaning();
    }
}

bool Dictionary::correct(string word, string newMeaning)
{
    auto val = words.find(WordMeaning(word,""));
    if(val == WordMeaning("","")){
        words.insert(WordMeaning(word,newMeaning));
        return false;
    }else{
        val.setMeaning(newMeaning);
        return true;
    }
}

void Dictionary::print() const {
    for (iteratorBST<WordMeaning> it = words.begin(); it != words.end(); it++) {
        std::cout << (*it).getWord() << ": " << (*it).getMeaning() << std::endl;
    }
}

