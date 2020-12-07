#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    unsigned  initialSize = objs.size();
	for(auto it=objs.begin();it < objs.end(); it++){
	    if(it->getWeight() <= boxCapacity){
	        objects.push(*it);
	        objs.erase(it);
	        it--;
	    }
	}
	return initialSize-objs.size();
}

Box PackagingMachine::searchBox(Object& obj){
	Box b(boxCapacity);
	HeapBox temp;
	bool found = false;
	while(!boxes.empty()){
	    Box front = boxes.top();
	    boxes.pop();
	    if(!found){
	        if(obj.getWeight() <= front.getFree()){
	            b = front;
	            found = true;
	        }else temp.push(front);
	    }else temp.push(front);
	}
	boxes = temp;
	return b;
}

unsigned PackagingMachine::packObjects() {
    HeapObj tempobj;
    while (!objects.empty()){
        Object obj = objects.top();
        objects.pop();
        Box box = searchBox(obj);
        if(obj.getWeight() <= box.getFree()){
            box.addObject(obj);
        } else tempobj.push(obj);
        boxes.push(box);
    }
    objects = tempobj;
	return boxes.size();
}

string PackagingMachine::printObjectsNotPacked() const {
	if(objects.empty()) return "No objects!\n";
	HeapObj temp = objects;
	stringstream ss;
	while (!temp.empty()){
	    Object obj = temp.top();
	    temp.pop();
	    ss << obj << "\n";
	}
	return ss.str();
}

Box PackagingMachine::boxWithMoreObjects() const {
    if(boxes.empty()) throw MachineWithoutBoxes();
    Box b;
    HeapBox temp = boxes;
    while (!temp.empty()){
        Box tempB = temp.top();
        temp.pop();
        if(tempB.getSize() > b.getSize()){
            b = tempB;
        }
    }
	return b;
}