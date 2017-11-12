#include <iostream>
#include <exception>
#include "sortedList.h"
#include "model.h"
#include "node.h"
#include "myString.h"

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

bool SortedList::insert(Model* newModel) {
	int targetId = newModel->getId();

	if (newModel == NULL) {
		return false;
	}

	// If head don't exist, newModel is head
	if (head == NULL) {
		head = new Node<Model*>(newModel);
		return true;
	}
	
	Node<Model*>* currentNode = head;

	// Walks through whole list
	while (currentNode != NULL) {

		int currentId = currentNode->getData()->getId();
		
		// If id already exists don't insert
		if (currentId == targetId) {
			return false;
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
			return true;
		}

		// Check if it's the last node in the list. If it's, insert newNode in the last position.
		if (currentNode->getNext() == NULL) {
			currentNode->setNext(new Node<Model*>(newModel));
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;	//Sanity check
}

bool SortedList::remove(int id) {
	Node<Model*>* trashNode = findNode(id);

	// If found the node in the list, delete it.
	if (trashNode != NULL) {
		Node<Model*>* nextNode = trashNode->getNext();
		Node<Model*>* prevNode = trashNode->getPrev();
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
		if (trashNode == head) {
			head = NULL;
		}
		delete trashNode;
		return true;
	}
	return false;
}

bool SortedList::edit(Model* modifiedModel) {
	Node<Model*>* nodeToModify = findNode(modifiedModel->getId());
	if (nodeToModify == NULL) {
		return false;
	}
	nodeToModify->setData(modifiedModel);
	return true;
}

Node<Model*>* SortedList::findNode(int id) {
	Node<Model*>* currentNode = head;
	while (currentNode != NULL) {
		int currentId = currentNode->getData()->getId();
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

Model* SortedList::find(int id) {
	Node<Model*>* node = findNode(id);
	if (node != NULL) {
		return node->getData();
	}
	return NULL;
}

string SortedList::listAll() {
	string result = "";
	Node<Model*>* currentNode = head;
	int currentId;
	while (currentNode != NULL) {
		currentId = currentNode->getData()->getId();
		result.append(numberToString(currentId) + "\n");
		currentNode = currentNode->getNext();
	}
	return result;
}
