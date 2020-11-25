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

void Dictionary::readDictionary(ifstream &f)
{
    std::string word, meaning;
    while(!f.eof()){
        getline(f,word);
        getline(f,meaning);
        words.insert(WordMeaning(word,meaning));
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    return "";
}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    return true;
}

void Dictionary::print() const
{
    for(iteratorBST<WordMeaning> it = words.begin(); it < words.end(); it++){

    };

