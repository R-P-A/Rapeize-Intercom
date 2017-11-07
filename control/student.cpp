#include <iostream>
#include <exception>
#include "student.h"
#include "myString.h"

using namespace std;

#define maximumAbsence 10

Student::Student() {
	id = 0;
	name = "";
	grade1 = 0;
	grade2 = 0;
	creationTime = "";
}

Student::Student(int id) {
	Model::setId(id);
}

Student::~Student() { }

string Student::getName() {
	return name;
}

void Student::setName(string value) {
	name = value;
}

float Student::getGrade1() {
	return grade1; 
}

bool Student::setGrade1(float value) {
	if (value < 0 || value > 10) {
		grade1 = 0;
		return false;
	}
	grade1 = value;
	return true;	
}

float Student::getGrade2() {
	return grade2; 
}

bool Student::setGrade2(float value) {
	if (value < 0 || value > 10) {
		grade2 = 0;
		return false;
	}
	grade2 = value;
	return true;
}

string Student::getCreationTime() {
	return creationTime;
}

void Student::setCreationTime(string value) {
	creationTime = value;
}

string Student::getModificationTime() {
	return modificationTime;
}

void Student::setModificationTime(string value) {
	modificationTime = value;
}

float Student::getFinalGrade() {
	float finalGrade = (grade1 + grade2)/2;
	return finalGrade;
}

string Student::toString() {
	string result;
	float finalGrade = getFinalGrade();
	result = "Name:\t\t" + name + "\n";
	result.append("Id:\t\t" + numberToString(id) + "\n");
	result.append("Grade 1:\t" + numberToString(grade1) + "\n");
	result.append("Grade 2:\t" + numberToString(grade2) + "\n");
	result.append("Final Grade:\t" + numberToString(finalGrade) + "\n");
	result.append("Created:\t" + creationTime + "\n");
	result.append("Last Modified:\t" + modificationTime + "\n");
	return result;
}
