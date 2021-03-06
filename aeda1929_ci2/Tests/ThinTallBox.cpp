#include "ThinTallBox.h"
#include "WideFlatBox.h"

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if(object.getSize() + getContentSize() <= getCapacity()){
        setContentSize(getContentSize()+object.getSize());
        objects.push(object);
        return;
    }
    throw ObjectDoesNotFitException();
}

void ThinTallBox::sortObjects() {
	WideFlatBox wideFlatBox(getCapacity());
	while(!objects.empty()){
	    wideFlatBox.insert(removeNext());
	}
	wideFlatBox.sortObjects();
	while(!wideFlatBox.empty()){
	    objects.push(wideFlatBox.removeNext());
	}
}
