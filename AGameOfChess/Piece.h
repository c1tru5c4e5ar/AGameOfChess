#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

#include<vector>
#include<utility>

class Piece
{
public:
	bool pieceColor;
	/*	True : White	False : Black	*/

	char pieceType;
	/*
	K : King
	Q : Queen
	B : Bishop
	P : Pawn
	R : Rook
	N : Knight
	O : NULL
	*/
	std::pair<int, int> piecePos;
	std::vector<std::pair<int, int>> possibleMoves;

	bool isFirstMove;
	bool isCaptured;

	bool iscastlingPossible;
	bool isEnPassantPossible;
	bool ispromotionPossible;

	bool isinCheck; //For kings only

	//sfml
	//Image/Icon of Piece
	//void loadIcon();
	Piece();
	~Piece();

	void assign(char pType, bool pCol, int piecePosR, int piecePosC);
	bool isEqual(Piece &P);

	//SFML:
	sf::Texture image;
	sf::Sprite icon;
	float Ox, Oy;//Origin

	void loadIcon();
	void setPos();
	//bool getSpecialMove()
};

