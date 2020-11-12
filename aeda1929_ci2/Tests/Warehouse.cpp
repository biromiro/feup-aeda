#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(),obj.end(),[](Object obj1, Object obj2){
        return obj1 < obj2;
    });
    for(const auto elem: obj){
        objects.push(elem);
    }
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
     queue<Object> newQueue;
     Object current;
     size_t sizeOfQueue = objects.size();
     while (!objects.empty()){
         current = objects.front();
         objects.pop();
         if(current.getSize() <= maxSize)
             break;
         newQueue.push(current);
     }
     while (!objects.empty()){
         newQueue.push(objects.front());
         objects.pop();
     }
    objects = newQueue;
     if(newQueue.size() == sizeOfQueue)
         return Object("dummy", maxSize);
     else return current;

}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(const auto elem: boV){
        boxes.push(elem);
    }
    return boxes.size();
}

void Warehouse::processBox(ThinTallBox& box){
    queue<Object> newQueue;
    Object current;
    size_t sizeOfQueue = objects.size();
    while (!objects.empty()){
        current = objects.front();
        objects.pop();
        if(current.getSize() <= box.getCapacity()-box.getContentSize()) {
            break;
        }
        newQueue.push(current);
    }
    while (!objects.empty()){
        newQueue.push(objects.front());
        objects.pop();
    }
    objects = newQueue;
    if(newQueue.size() == sizeOfQueue)
        box.insert(Object("dummy", 0));
    else box.insert(current);
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    queue<ThinTallBox> newQueue;
    while(!boxes.empty()){
        if(boxes.front().getCapacity() == boxes.front().getContentSize() ){
            res.push_back(boxes.front());
            boxes.pop();
        }else if(boxes.front().getDays() == 0){
            processBox(boxes.front());
            res.push_back(boxes.front());
            boxes.pop();
        }else{
            processBox(boxes.front());
            boxes.front().setDaysToSend(boxes.front().getDays()-1);
            newQueue.push(boxes.front());
            boxes.pop();
        }
    }
    return res;
}

