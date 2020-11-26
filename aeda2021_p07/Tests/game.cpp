#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

BinaryTree<Circle>* makeTree(int h, vector<int> &points, vector<bool> &states, int pos = 0){
    Circle* c = new Circle(points.at(pos),states.at(pos));
    if(h==0) return new BinaryTree<Circle>(*c);
    else{
        return new BinaryTree<Circle>(*c,*makeTree(h-1,points,states,2*pos+1),*makeTree(h-1,points,states,2*pos+2));
    }
}



Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    if(points.empty() || states.empty()) return;
    game = *(makeTree(h,points,states));

}

string Game::writeGame()
{
    stringstream ss;
    for(BTItrLevel<Circle> it = game; !it.isAtEnd(); it.advance()){
        ss << it.retrieve().getPoints() << "-" << (it.retrieve().getState() ? "true" : "false") << "-" << it.retrieve().getNVisits() << "\n";
    }
	return ss.str();
}

int Game::move()
{
    BTItrLevel<Circle> it = game;
    int p = 1, prev = 0;
    Circle final = game.getRoot();
    bool turnRight = game.getRoot().getState();
    game.getRoot().changeState();
    game.getRoot().addNVisits();
    it.advance();
    while(!it.isAtEnd()){
        if((!turnRight && p== 2*prev +1) || (turnRight && p== 2*prev +2)){
                final = it.retrieve();
                prev = p;
                turnRight = it.retrieve().getState();
                it.retrieve().changeState();
                it.retrieve().addNVisits();
        }
        it.advance();
        p++;
    }
	return final.getPoints();
}

int Game::mostVisited()
{
    BTItrLevel<Circle> ite = game;
    ite.advance();
    int max = 0;
    for(auto it = ite; !it.isAtEnd(); it.advance()){
        int nVisits = it.retrieve().getNVisits();
        if(nVisits > max) max = nVisits;
    }
	return max;
}
