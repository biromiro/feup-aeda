/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
    if(distance > cr.getDistance()) return true;
    else if(distance < cr.getDistance()) return false;
	else return services.size() < cr.services.size();
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = nullptr;
    unsigned h1Init = h1;
	for(BSTItrIn<FilmTime> bItr(timetable); !bItr.isAtEnd(); bItr.advance()){
	    FilmTime film = bItr.retrieve();
        if(film.getHour() > h1) break;
        else{
            res = film.getFilm();
            h1Init = film.getHour();
        }
	}
	h1 = h1Init;
	return res;
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	bool modify = true, found = false;
	FilmTime filmToChange(0, nullptr,0);
    for(BSTItrIn<FilmTime> bItr(timetable); !bItr.isAtEnd(); bItr.advance()){
        FilmTime film = bItr.retrieve();
        if(film.getHour() == h1 && film.getRoomID() == room1){
            filmToChange = film;
            found = true;
        }
        if(film.getHour() == h2 && film.getRoomID() == room1){
            modify = false;
        }
    }
    if(found && modify){
        timetable.remove(filmToChange);
        timetable.insert(FilmTime(h2, filmToChange.getFilm(), room1));
        return true;
    }else return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 1;
	FilmTime currentFilm(0, nullptr,0);
	FilmTime film(h1, f1, 1);
    for(BSTItrIn<FilmTime> bItr(timetable); !bItr.isAtEnd(); bItr.advance()){
        currentFilm = bItr.retrieve();
        if(currentFilm.getHour() > h1){
            if(numberOfRooms >= roomToUse){
                timetable.insert(FilmTime(h1,f1,roomToUse));
                return roomToUse;
            }else return 0;
        }
        roomToUse = currentFilm.getRoomID() + 1;
    }
    if(numberOfRooms >= film.getRoomID()){
        timetable.insert(film);
        return film.getRoomID();
    }else return 0;

}






