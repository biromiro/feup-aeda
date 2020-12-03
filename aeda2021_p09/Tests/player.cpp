#include <algorithm>
#include "player.h"

void Player::addBet(const Bet& b){
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const
{
	return std::count_if(bets.begin(),bets.end(),[num](const Bet& bet){
	    return bet.getNumbers().find(num) != bet.getNumbers().end();
	});
}

tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	for(const auto& elem: bets){
	    if(std::count_if(elem.getNumbers().begin(),elem.getNumbers().end(),[&draw](unsigned num){
	       return draw.find(num) != draw.end();
	    }) > 3){
	        res.insert(elem);
	    }
	}
	return res;
}
