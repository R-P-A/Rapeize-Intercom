#include <iostream>
#include <exception>
#include "sortedList.h"
#include "model.h"
#include "node.h"

using namespace std;

SortedList::SortedList() {
	head = NULL;
}

SortedList::~SortedList() {
	Node<Model*>* currentNode = head;
	while (head != NULL) {
		currentNode = currentNode->getNext();
		delete head;
		head = currentNode;
	}
	head = NULL;	// Officially empty
}

void SortedList::insert(Model* newModel) {
	int targetId = newModel->getId();

	if (newModel == NULL) {
		throw "Inserted NULL Model";
	}

	// If head don't exist, newModel is head
	if (head == NULL) {
		head = new Node<Model*>(newModel);
		return;
	}
	
	Node<Model*>* currentNode = head;

	// Walks through whole list
	while (currentNode != NULL) {

		int currentId = currentNode->getData()->getId();
		
		// If id already exists don't insert
		if (currentId == targetId) {
			throw "Id already exists";
		}

		// It's sorted, so if currentId > targetId try to insert before the current node
		if (currentId > targetId) {
			Node<Model*>* newNode = new Node<Model*>(newModel);
			Node<Model*>* prevNode = currentNode->getPrev();

			if (prevNode != NULL) {
				prevNode->setNext(newNode);
			} else {
				head = newNode;
			}
			currentNode->setPrev(newNode);
			return;
		}

		// Check if it's the last node in the list. If it's, insert newNode in the last position.
		if (currentNode->getNext() == NULL) {
			currentNode->setNext(new Node<Model*>(newModel));
			return;
		}
		currentNode = currentNode->getNext();
	}
	return;	//Sanity check
}

Model* SortedList::search(unsigned long int id) {
	Node<Model*>* node = searchNode(id);
	if (node != NULL) {
		return node->getData();
	}
	return NULL;
}

void SortedList::update(Model* modifiedModel) {
	Node<Model*>* nodeToModify = searchNode(modifiedModel->getId());
	if (nodeToModify == NULL) {
		throw "Id not found";
	}
	nodeToModify->setData(modifiedModel);
	return;
}

void SortedList::remove(unsigned long int id) {
	Node<Model*>* trashNode = searchNode(id);

	// If found the node in the list, delete it.
	if (trashNode != NULL) {
		Node<Model*>* nextNode = trashNode->getNext();
		Node<Model*>* prevNode = trashNode->getPrev();

		if (trashNode == head) {
			head = NULL;
		}
		if (nextNode != NULL) {
			nextNode->setPrev(prevNode);
			// New head if it's the new first node.
			if (prevNode == NULL) {
				head = nextNode;
			}
		}
		if (prevNode != NULL) {
			prevNode->setNext(nextNode);
		}
		delete trashNode;
		return;
	}
	throw "Id not found";
}

Node<Model*>* SortedList::searchNode(unsigned long int id) {
	Node<Model*>* currentNode = head;
	while (currentNode != NULL) {
		unsigned long int currentId = currentNode->getData()->getId();
		if (currentId == id) {
			return currentNode;
		}
		if (currentId > id) {
			return NULL;
		}
		currentNode = currentNode->getNext();
	}
	return NULL;
}

string SortedList::listAll() {
	string result = "";
	Node<Model*>* currentNode = head;
	unsigned long int currentId;
	while (currentNode != NULL) {
		currentId = currentNode->getData()->getId();
		result.append(to_string(currentId) + "\n");
		currentNode = currentNode->getNext();
	}
	return result;
}
