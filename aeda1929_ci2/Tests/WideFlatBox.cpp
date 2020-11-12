#include <algorithm>
#include "WideFlatBox.h"

WideFlatBox::WideFlatBox(double capacity) : Box(capacity) {
}

void WideFlatBox::insert(Object object) {
	if(getContentSize()+object.getSize() <= getCapacity()) {
		objects.push_back(object);
		setContentSize(getContentSize()+object.getSize());
	} else {
		throw ObjectDoesNotFitException();
	}
}

const Object& WideFlatBox::next() const {
	return objects[0];
}

void WideFlatBox::sortObjects() {
	sort(objects.begin(), objects.end());
}


void WideFlatBox::remove(Object object) {
    for(const auto elem: objects){
        if(object == elem){
            setContentSize(getContentSize()-elem.getSize());
            objects.erase(std::remove(objects.begin(),objects.end(),elem),objects.end());
            return;
        }
    }
    throw InaccessibleObjectException(object);
}
