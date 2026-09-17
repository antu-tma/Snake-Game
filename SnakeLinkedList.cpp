#include "SnakeLinkedList.h"
#include <iostream>
#include <sstream>

// SnakeListNode
string SnakeListNode::toString() const {
	ostringstream oss;
	oss << "(row = " << _row << ", col = " << _col << ")";

	return oss.str();
}

// SnakeLinkedList
SnakeLinkedList::~SnakeLinkedList() {
	SnakeListNode *curNode = _head;
	while (curNode) {
		SnakeListNode *nextNode = curNode->nextNode();
		delete curNode;
		curNode = nextNode;
	}
}

void SnakeLinkedList::pushFront(int row, int col) {
	_head = new SnakeListNode(row, col, _head);
}

void SnakeLinkedList::popFront() {
	if (SnakeListNode *oldHead = _head) {
		_head = _head->nextNode();
		delete oldHead;
	}
}

void SnakeLinkedList::pushBack(int row, int col) {
	SnakeListNode *node = new SnakeListNode(row, col, nullptr);
	if (!_head) {
		_head = node;
	} else {
		tail()->setNextNode(node);
	}
}

void SnakeLinkedList::popBack() {
	if (!_head) {
	} else if (!_head->nextNode()) {
		delete _head;
		_head = nullptr;
	} else {
		SnakeListNode *curNode = _head;
		while (curNode->nextNode()->nextNode()) {
			curNode = curNode->nextNode();
		}
		delete curNode->nextNode();
		curNode->setNextNode(nullptr);
	}
}

int SnakeLinkedList::length() const {
	int result = 0;
	SnakeListNode *curNode = _head;
	while (curNode) {
		result++;
		curNode = curNode->nextNode();
	}

	return result;
}

SnakeListNode *SnakeLinkedList::tail() const {
	SnakeListNode *prevNode = nullptr;
	SnakeListNode *curNode = _head;
	while (curNode) {
		prevNode = curNode;
		curNode = curNode->nextNode();
	}
	
	return prevNode;
}

void SnakeLinkedList::printSnake() const {
	SnakeListNode *curNode = _head;
	int len = length();
	cout << "length = " << len;
	
	if (len > 1) {
		cout << ", head = " << head()->toString();
		cout << ", tail = " << tail()->toString();
	}
	if (len == 1) {
		cout << ", head = tail = " << head()->toString();
	}
	cout << endl;

	while (curNode != nullptr) {
		cout << " " << curNode->toString() << endl;
		curNode = curNode->nextNode();
	}

	cout << endl;
}
