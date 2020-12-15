#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
	for(auto& elem: properties){
	    bool found = false;
	    PropertyTypeItem pp(elem->getAddress(), elem->getPostalCode(), elem->getTypology(), elem->getPrice());
	    pp.addItems(elem);
        BSTItrIn<PropertyTypeItem> bItr(catalogItems);
        for(; !bItr.isAtEnd(); bItr.advance()){
            auto& obj = bItr.retrieve();
            if(obj == pp){
                obj.addItems(elem);
                found = true;
                break;
            }
        }
	    if(!found) catalogItems.insert(pp);
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	for(const auto& elem: properties){
	    if(property->getTypology() == elem->getTypology() && property->getPostalCode() == elem->getPostalCode() &&
	       property->getAddress() == elem->getAddress() && elem->getReservation() == tuple<Client*,int>()){
            temp.push_back(elem);
	    }
	}
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    PropertyTypeItem pp(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
    BSTItrIn<PropertyTypeItem> bItr(catalogItems);
    for(; !bItr.isAtEnd(); bItr.advance()){
        auto& obj = bItr.retrieve();
        if(obj == pp){
            for(auto &elem: obj.getItems()){
                if(elem->getReservation() == tuple<Client*,int>() && elem->getPrice()*(1-percentage/100.0) < property->getPrice()){
                    client->addVisiting(property->getAddress(), property->getPostalCode(), property->getTypology(), to_string(elem->getPrice()));
                    tuple<Client*,int> reservation(client,elem->getPrice()*(1-percentage/100.0));
                    elem->setReservation(reservation);
                    return true;
                }
            }
        }
    }
	return false;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
	listingRecords.insert(client);
}

void REAgency::deleteClients() {
    bool rr = true;
    while(rr){
        rr = false;
        for(auto itr = listingRecords.begin(); itr != listingRecords.end(); itr++) {
            if (itr->getClientPointer()->getVisitedProperties().empty()) {
                listingRecords.erase(itr);
                rr = true;
                break;
            }
        }
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
	for(const auto& elem: candidates){
	    float reservedByVisitedRatio = 0;
	    for(const auto& property: properties){
	        if(get<0>(property->getReservation())->getEMail() == elem.getEMail())
	            reservedByVisitedRatio += 1;
	    }
	    reservedByVisitedRatio /= elem.getVisitedProperties().size();
	    if(reservedByVisitedRatio > min)
	        clientProfiles.push(elem);
	}
}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> clientProfilesTemp;

	while(!clientProfiles.empty()){
	    auto profile = clientProfiles.top();
	    clientProfiles.pop();
	    clientProfilesTemp.push(profile);
	    if(profile.getVisiting() == tuple<string,string,string,string>()){
            continue;
	    }
	    Property* currentProperty;
	    int minPostalCodeDiff = 9999999;
	    for(const auto& elem: properties){
	        int val = abs(stoi(elem->getPostalCode()) - stoi(get<1>(profile.getVisiting())));
            if(val != 0 &&  val < minPostalCodeDiff && get<0>(elem->getReservation()) == NULL){
                currentProperty = elem;
                minPostalCodeDiff = val;
            }
	    }
	    tempProperties.push_back(currentProperty);
	}

	clientProfiles = clientProfilesTemp;
	return tempProperties;
}
