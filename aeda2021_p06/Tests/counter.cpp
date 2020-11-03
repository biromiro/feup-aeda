#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"

unsigned randomNumberGenerator(unsigned n1, unsigned n2){
    if(n1>n2)
        return randomNumberGenerator(n2,n1);
    return (rand() % (n2-n1+1)) + n1;
}

Client::Client() {
    numGifts = randomNumberGenerator(1,5);
}

unsigned Client::getNumGifts() const {
    return numGifts;
}

Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextEnter = randomNumberGenerator(1,20);
    nextLeave = 0;
    numAttendedClients = 0;
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if(clients.empty())
        throw EmptyQueue();
    return clients.front();
}

void Counter::enter(){
    Client newClient;
    if(clients.empty())
        nextLeave = actualTime + newClient.getNumGifts()*wrappingTime;
    nextEnter = randomNumberGenerator(actualTime+1,actualTime + 20);
    clients.push(newClient);
    std::cout << "time = " << actualTime << "\n" << "new costumer arrived with " << newClient.getNumGifts() << " gifts" << std::endl;
}

void Counter::leave(){
    try{
        getNextClient();
    } catch (const EmptyQueue& e) {
        std::cout << "Tried to leave the queue, but the queue is empty.";
    }
    std::cout << "time = " << actualTime << "\n" << "the costumer who left had " << clients.front().getNumGifts() << " gifts" << std::endl;
    clients.pop();
    if(!clients.empty())
        nextLeave = actualTime + clients.front().getNumGifts()*wrappingTime;
    numAttendedClients++;
}

void Counter:: nextEvent()
{
    if (nextEnter <= nextLeave || clients.empty()) {
        actualTime = nextEnter;
        enter();
    }else if (nextEnter >= nextLeave && !clients.empty()) {
        actualTime = nextLeave;
        leave();
    }
}


ostream & operator << (ostream & out, const Counter & c2)
{
    out << c2.numAttendedClients << " customers were attended. " << c2.clients.size() << " customers are waiting." << std::endl;
    return out;
}


