#include "PropertyTypeItem.h"

PropertyTypeItem::PropertyTypeItem(string address, string postalCode, string typology, int maxPrice) {
	this->address = address;
	this->postalCode = postalCode;
	this->typology = typology;
	this->maxPrice = maxPrice;
}

string PropertyTypeItem::getAddress() const {
	return this->address;
}

string PropertyTypeItem::getPostalCode() const {
	return this->postalCode;
}

string PropertyTypeItem::getTypology() const {
	return this->typology;
}

int PropertyTypeItem::getMaxPrice() const {
	return this->maxPrice;
}

vector<Property*> PropertyTypeItem::getItems() const {
	return this->items;
}

void PropertyTypeItem::setItems(vector<Property*> properties) {
	items = properties;
}

void PropertyTypeItem::addItems(Property* property) {
    if(property->getPrice() > maxPrice) maxPrice = property->getPrice();
	this->items.push_back(property);
}

bool PropertyTypeItem::operator<(const PropertyTypeItem &pti1) const {
	if(address < pti1.getAddress()){
	    return true;
	}else if(address > pti1.getAddress()){
	    return false;
	}else if(postalCode < pti1.getPostalCode()){
	    return true;
	}else if(postalCode > pti1.getPostalCode()){
	    return false;
	}else if(typology < pti1.getTypology()){
	    return true;
	}else if(typology > pti1.getTypology()){
	    return false;
	}else return maxPrice < pti1.getMaxPrice();
}

bool PropertyTypeItem::operator==(const PropertyTypeItem &pti1) const {
	return address == pti1.getAddress() && postalCode == pti1.getPostalCode() && typology == pti1.getTypology();
}
