#include "bet.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool Bet::contains(unsigned num) const
{
	return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n){
    for(const auto& elem:values){
        if(numbers.size() < n) numbers.insert(elem);
        else return;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const
{
	return std::count_if(numbers.begin(),numbers.end(),[&draw](unsigned i){
	    return draw.find(i) != draw.end();
	});
}
