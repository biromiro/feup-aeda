#include "game.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

Game::Game()
{
    kids = list<Kid>();
}

Game::Game(list<Kid>& l2)
{
    kids = l2;
}

void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

list<Kid> Game::getKids() const
{
    return kids;
}

string Game::write() const
{
    string res = "";
    for(const auto& elem: kids){
        res += (elem.write() + '\n');
    }
    return res;
}

Kid& Game::loseGame(string phrase)
{
    unsigned int numWords = numberOfWords(phrase);
    unsigned int saveStatusNumWords = numWords;
    list<Kid> kidsCopy = kids;
    if(kidsCopy.size() == 0)
        throw length_error("No kids to play");
    while(kidsCopy.size() > 1){
        auto pointedKid = kidsCopy.begin();
        while(numWords-1 > 0){
            if((++pointedKid) == kidsCopy.end())
                pointedKid = kidsCopy.begin();
            numWords--;
        }
        kidsCopy.erase(pointedKid);
        numWords = saveStatusNumWords;
    }
    return kidsCopy.front();
}

list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> removedElems = kids;
    kids.remove_if([&id](const Kid& kid){return kid.getAge()>id;});
    removedElems.remove_if([&id](const Kid& kid){return kid.getAge()<=id;});
    return removedElems;
}


void Game::setKids(const list<Kid>& l1)
{
    list<Kid> replaced = l1;
    kids.splice(kids.end(),replaced);
}

bool Game::operator==(Game& g2)
{
    if(kids.size() != g2.getKids().size())
        return false;
    list<Kid> g2Kids = g2.getKids();
    list<Kid>::iterator it= g2Kids.begin();
	for(auto const& elem:kids){
	    if(!(elem == (*it))){
	        return false;
	    }
	    advance(it,1);;
	}
	return true;
}

list<Kid> Game::shuffle() const
{
    list<Kid> shuffled, kidCopy = kids;
    unsigned int randomNumber;
    list<Kid>::iterator it ;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator

    while(kidCopy.size()>0){
        it = kidCopy.begin();
        std::uniform_int_distribution<> distr(0, kidCopy.size()-1); // define the range
        randomNumber = distr(gen);
        advance(it,randomNumber);
        shuffled.push_back((*it));
        kidCopy.erase(it);
    }
    return shuffled;
}
