#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;

    bool operator==(const WordMeaning &rhs) const;

    bool operator!=(const WordMeaning &rhs) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


class WordInexistent
{
    BST<WordMeaning> words;
    std::string word;
public:
    explicit WordInexistent(const BST<WordMeaning>& words,std::string word) : words(words), word(std::move(word)){};
    WordMeaning getWordMeaningBefore() const{
        if(words.isEmpty()) return WordMeaning("","");
        for (iteratorBST<WordMeaning> it = words.begin(); it != words.end(); it++) {
            auto itVal = it;
            itVal++;
            if(itVal == words.end()){
                if((*it) < WordMeaning(word,"")) return *it;
                else return WordMeaning("","");
            }
            else if(WordMeaning(word,"") < (*(itVal))){
                return (*it);
            }
        }
    }

    WordMeaning getWordMeaningAfter() const{
        if(words.isEmpty()) return WordMeaning("","");
        for (iteratorBST<WordMeaning> it = words.begin(); it != words.end(); it++) {
            auto itVal = it;
            itVal++;
            if(itVal == words.end()){
                if((*it) < WordMeaning(word,"")) return WordMeaning("","");
                else return *it;
            }
            else if(WordMeaning(word,"") < (*(itVal))){
                return (*itVal);
            }
        }
    }
    string getWordBefore() const { 
        return getWordMeaningBefore().getWord();
    }
    string getMeaningBefore() const { return getWordMeaningBefore().getMeaning(); }
    string getWordAfter() const { return getWordMeaningAfter().getWord(); }
    string getMeaningAfter() const { return getWordMeaningAfter().getMeaning(); }
};

#endif