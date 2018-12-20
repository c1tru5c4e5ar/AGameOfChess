#pragma once
#include<array>
#include<iostream>
#include<algorithm>

#include "Piece.h"

#define pii std::pair<int,int>

class ChessBoard
{
private:
	Piece mainBoard[8][8];		//To display pieces on screen
	bool highlightBoard[8][8];	//To display highlighted squares on screen

public:
	ChessBoard();
	~ChessBoard();

	Piece& getElementOnPos(int posR, int posC);

	void swapElements(pii & p1, pii & p2);
	void moveElement(pii &p1, pii &p2);

	void highlightElement(pii p);

	void printmainBoard();
	void printhiglightBoard();
	//void displaymainBoard()
		//sfml
	//void displayhighlightBoard()
		//sfml
};

