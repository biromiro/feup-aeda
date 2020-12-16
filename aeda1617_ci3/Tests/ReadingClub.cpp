/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    for(const auto& elem: books){
        bool added = false;
        for(BSTItrIn<BookCatalogItem> bItr(catalogItems); !bItr.isAtEnd(); bItr.advance()){
            BookCatalogItem book = bItr.retrieve();
            if(book.getTitle() == elem->getTitle() && book.getAuthor() == elem->getAuthor()){
                auto books = book.getItems();
                books.push_back(elem);
                catalogItems.remove(book);
                book.setItems(books);
                catalogItems.insert(book);
                added = true;
                break;
            }
        }
        if(!added){
            BookCatalogItem catalogItem(elem->getTitle(),elem->getAuthor(),elem->getYear());
            vector<Book*> books;
            books.push_back(elem);
            catalogItem.setItems(books);
            catalogItems.insert(catalogItem);
        }
    }
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	for(BSTItrIn<BookCatalogItem> bItr(catalogItems); !bItr.isAtEnd(); bItr.advance()){
	    auto bookCatalogItem = bItr.retrieve();
	    if(bookCatalogItem == BookCatalogItem(book->getTitle(),book->getAuthor(),0)){
	        for(const auto& elem: bookCatalogItem.getItems()){
	            if(elem->getReader() == nullptr){
	                temp.push_back(elem);
	            }
	        }
	    }
	}
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	auto availableBooks = getAvailableItems(book);
    if(availableBooks.empty()) return false;
    availableBooks.at(0)->setReader(reader);
    reader->addReading(book->getTitle(),book->getAuthor());
    return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
    userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	userRecords.erase(UserRecord(user));
	user->setEMail(newEMail);
	addUserRecord(user);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(const auto& elem: candidates){
	    if(elem.numReadings() >= min){
	        readerCandidates.push(elem);
	    }
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
    if(readerCandidates.empty()) return 0;
    auto winner = readerCandidates.top();
    readerCandidates.pop();
    int res = (readerCandidates.empty()) ? (0) : ((readerCandidates.top().numReadings() == winner.numReadings()) ? (0): (readerCandidates.size() + 1));
    readerCandidates.push(winner);
    if(res) champion = winner;
    return res;
}
























