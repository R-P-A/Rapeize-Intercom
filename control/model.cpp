#include <iostream>
#include <exception>
#include "model.h"

using namespace std;

int Model::getId() {
	return id;
}

void Model::setId(int value) {
	id = value;
}