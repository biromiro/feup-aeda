/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;
	for(const auto& elem: films){
	    for(const auto& actor: elem.film->getActors()){
	        if(actorName == actor) res.push_back(elem.film->getTitle());
	    }
	}
	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {
    FilmPtr fpt1;
    fpt1.film = nullptr;

    for(const auto& elem: films){
        if(elem.film->getTitle() == filmTitle){
            fpt1 = elem;
            break;
        }
    }

	if(fpt1.film != nullptr){
	    films.erase(fpt1);
	    fpt1.film->addActor(actorName);
	    films.insert(fpt1);
	}else{
	    list<string> actors;
	    actors.push_back(actorName);
	    Film* movie = new Film(filmTitle,actors);
	    fpt1.film = movie;
	    films.insert(fpt1);
	}

}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";
	auto tmpPrioQ = cinemas;
	bool found = false;
	while(!tmpPrioQ.empty()){
	    auto cinema = tmpPrioQ.top();
	    tmpPrioQ.pop();
	    auto services = cinema.getServices();
	    for(auto it = services.begin(); it != services.end(); it++){
            if(*it == service1){
                found = true;
                cName = cinema.getName();
                break;
            }
	    }
        if(found) break;
	}
	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	if(!cinemas.empty()){
	    auto top = cinemas.top();
	    if(top.getDistance() <= maxDistance){
	        cinemas.pop();
	        top.addService(service1);
	        cinemas.push(top);
            return;
	    }
	}
	throw CinemaNotFound();

}
