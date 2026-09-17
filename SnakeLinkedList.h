#ifndef __SNAKE_LINKED_LIST_H__
#define __SNAKE_LINKED_LIST_H__

#include <string>

using namespace std;


class SnakeListNode {
public:
  SnakeListNode(int row, int col, SnakeListNode *nextNode)
      : _row(row), _col(col), _nextNode(nextNode) {}

  int row() const { return _row; };
  int col() const { return _col; };

  SnakeListNode *nextNode() const { return _nextNode; };
  void setNextNode(SnakeListNode *nextNode) { _nextNode = nextNode; };

  string toString() const;

private:
  int _row;
  int _col;
  SnakeListNode *_nextNode;
};


class SnakeLinkedList {
public:
  virtual ~SnakeLinkedList();

  void pushFront(int row, int col);
  void popFront();

  void pushBack(int row, int col);
  void popBack();

  int length() const;

  SnakeListNode* head() const {return _head; };
  SnakeListNode* tail() const;

  void printSnake() const;

private:
  SnakeListNode *_head = nullptr;
};

#endif
