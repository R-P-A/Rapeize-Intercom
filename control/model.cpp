#include <iostream>
#include <exception>
#include "model.h"

using namespace std;

Model::Model() {
	id = 0;
}

Model::Model(unsigned long int value) {
	id = value;
}

unsigned long int Model::getId() {
	return id;
}

void Model::setId(unsigned long int value) {
	id = value;
}