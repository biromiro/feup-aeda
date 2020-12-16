/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"
#include <algorithm>

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    Expertize emptyExpertize("",0);
    Expertize addExpertize = getExpertize(expertizeAvailable,cost);
    if(!(addExpertize == emptyExpertize)){
        expertizes.remove(addExpertize);
    }else addExpertize = Expertize(expertizeAvailable,cost);

    vector<Student*> consultants = addExpertize.getConsultants();
    if(find(consultants.begin(),consultants.end(),student) == consultants.end()){
        consultants.push_back(student);
        addExpertize.setConsultants(consultants);
    }

    expertizes.insert(addExpertize);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	for(BSTItrIn<Expertize> bItr(expertizes); !bItr.isAtEnd(); bItr.advance()){
	    auto obj = bItr.retrieve();
        if(obj.getName() != project->getExpertize()) continue;
        if(obj.getCost() != project->getCost()) continue;
	    for(const auto& elem: obj.getConsultants()){
	        if(elem->getCurrentProject().empty()) temp.push_back(elem);
	    }
	}
	return temp;
}

bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	auto candidateStudents = getCandidateStudents(project);
	if(find(candidateStudents.begin(),candidateStudents.end(),student) == candidateStudents.end()) return false;
	else if(project->getConsultant() != nullptr) return false;

	student->addProject(project->getTitle());
	project->setConsultant(student);

	return true;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    students.insert(StudentPtr(student));
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	students.erase(StudentPtr(student));
	student->setEMail(newEMail);
	addStudent(student);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for(const auto& elem: candidates){
	    if(elem.getPastProjects().size() >= min){
	        activeStudents.push(elem);
	    }
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    if(activeStudents.empty()) return 0;
	auto topStudent = activeStudents.top();
	activeStudents.pop();
	if(!activeStudents.empty()){
        auto secondTopStudent = activeStudents.top();
        activeStudents.push(topStudent);
        if(secondTopStudent.getPastProjects().size() == topStudent.getPastProjects().size()){
            return 0;
        }
	}
	studentMaximus = topStudent;
	return activeStudents.size();

}





















