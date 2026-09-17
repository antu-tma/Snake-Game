#include "ConsoleInput.h"
#include "Snake.h"

Snake::Snake() {
	pushBack(5, 5);
	pushBack(5, 4);
	pushBack(5, 3);
}

CommandKey Snake::direction() {
	CommandKey result = CommandKey('q');
	if (_dRow == 0) {
		result = (_dCol == 1) ? arrowRightKey : arrowLeftKey;
	} else if (_dCol == 0) {
		result = (_dRow == 1) ? arrowDownKey : arrowUpKey;
	}
	return result;
}

// Returns true if the next position of the snake's head
// (as determined by the snake's direction of travel)
// will result in a crash. A crash occurs when the snake's
// head is either out of bounds or intersecting
// with any of the snake's nodes.
bool Snake::willCrash(const ConsoleGrid *grid) const {
	int nextRow = head()->row() + _dRow;
	int nextCol = head()->col() + _dCol;

	bool inBounds = grid->isValidCoord(nextRow, nextCol);
	bool intersect = intersects(nextRow, nextCol);
	return !inBounds || intersect;
} 

// Returns whether the position matches the coordinates of any
// of the snake's nodes.
bool Snake::intersects(int row, int col) const {
	SnakeListNode *curNode = head();
	bool intersects = false;
	while (curNode) {
		if (curNode->row() == row && curNode->col() == col) {
			intersects = true;
			break;
		}
		curNode = curNode->nextNode();
	}
	return intersects;
}

// Draws _each_ of the snake's nodes on the ConsoleGrid.
// This is called by main(). It is called to 1) start the game and to
// 2) change the snake's color after eating.
// Your code should **never** need to call this.
void Snake::drawChars(ConsoleGrid *grid) const {
	SnakeListNode *curNode = head();
	while (curNode) {
		char c = (curNode == head()) ? _headGlyph : _glyph;
		grid->drawCharAt(curNode->row(), curNode->col(), c, _color); 
		curNode = curNode->nextNode();
	}
}

// Update _dRow, _dCol to indicate the direction of next step.
// For those building an Autonomous subclass, overide this method.
// The overriden method should ignore the cmd parameter.
// This base class implementation should ignore grid and candy-coords.
void Snake::steer(char cmd, const ConsoleGrid *grid, int candyRow, int candyCol) {
	switch (cmd) {
	case arrowRightKey:
		if (_dCol != -1) { _dCol = 1; } // AT: not required to check _dCol/_dRow
		_dRow = 0;
		break; 
	case arrowLeftKey:
		if (_dCol != 1) { _dCol = -1; }
		_dRow = 0;
		break;
	case arrowUpKey:
		if (_dRow != 1) { _dRow = -1; }
		_dCol = 0;
		break;
	case arrowDownKey:
		if (_dRow != -1) { _dRow = 1; }
		_dCol = 0;
		break;
	default:
		break;
	}
}

// Have the snake move *one* step in its direction of travel.
// Snakes _move_ by adding a head node and removing their tail. They
// _grow_ by adding a head node and **not** removing their tail.
// Draw and erase only the nodes that are necessary to perform the step.
void Snake::step(ConsoleGrid *grid) {
	int newHeadRow = head()->row() + _dRow;
	int newHeadCol = head()->col() + _dCol;

	grid->drawCharAt(head()->row(), head()->col(), _glyph, _color);

	pushFront(newHeadRow, newHeadCol);
	grid->drawCharAt(newHeadRow, newHeadCol, _headGlyph, _color);
	
	if (_calories > 0) {
		_calories--;
	} else {
		grid->eraseCharAt(tail()->row(), tail()->col());
		popBack();
	}
}

// eat() tells the snake that it has eaten a Candy with the given calories.
// In N subequent turns (where N is the number of calories eaten)
// the snake must increase its length by one segment per turn.
// Use calories as an indicator that the snake should grow
// in the step() method. Decrement when the snake grows, and
// grow when _calories are > 0.
void Snake::eat(int calories) {
	_calories += calories;
}


