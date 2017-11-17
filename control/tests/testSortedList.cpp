#include <iostream>
#include "sortedList.h"
#include "model.h"

using namespace std;

int main() {
	SortedList* tempList = new SortedList();
	Model* model1 = new Model(1);
	Model* model2 = new Model(2);
	Model* model3 = new Model(3);
	Model* model4 = new Model(4);
	Model* model5 = new Model(5);

	cout << "Inserting all models unsorted plus model 4 two times" << endl;
	try {
		tempList->insert(model4);
	} catch (const char* e) {
		cout << e << endl;
	}
	try {
		tempList->insert(model3);
	} catch (const char* e) {
		cout << e << endl;
	}
	try {
		tempList->insert(model4);
	} catch (const char* e) {
		cout << e << endl;
	}
	try {
		tempList->insert(model2);
	} catch (const char* e) {
		cout << e << endl;
	}
	try {
		tempList->insert(model1);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << "Removing model 1 from the list" << endl;
	try {
		tempList->remove(model1->getId());
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << "Removing model 3 from the list" << endl;
	try {
		tempList->remove(model3->getId());
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << "Removing model 3 from the list again (model not existent)" << endl;
	try {
		tempList->remove(model3->getId());
	} catch (const char* e) {
		cout << e << endl << endl;
	}

	cout << "Editing model2 with model2 (final value must be the same without exception)" << endl;
	try {
		tempList->update(model2);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << "Editing model3 with model3 (Exception because id of model3 is not valid)" << endl;
	try {
		tempList->update(model3);
	} catch (const char* e) {
		cout << e << endl << endl;;
	}

	cout << "Find model4 and put model5 value equal to model4" << endl;
	try {
		model5 = tempList->search(model4->getId());
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << model5->getId() << endl << endl;

	cout << "Find a not existing id" << endl;
	try {
		tempList->search(10);
	} catch (const char* e) {
		cout << e << endl;
	}
	
	cout << "Removing model 2 from the list" << endl;
	try {
		tempList->remove(model2->getId());
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << "Removing model 4 from the list" << endl;
	try {
		tempList->remove(model4->getId());
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << tempList->listAll() << endl;

	cout << tempList->listAll() << endl;
	cout << "Checking to see if the memory of model3 was freed when deleting the model" << endl;
	cout << model3->getId() << endl;

	delete tempList;

	cout << "Checking to see if the memory of model4 and model5 (which are the same) was freed when deleting the tempList" << endl;
	cout << model4->getId() << endl;
	cout << model5->getId() << endl;
	return 0;
}