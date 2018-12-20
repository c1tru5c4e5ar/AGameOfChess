#pragma once

#include<string>
#include<vector>

#include"Piece.h"

class Player
{
public:
	std::string playerName;
	bool playerColor;

	std::vector<Piece> capturedPieces;

	Player();
	Player(std::string name, bool color);
	virtual ~Player();
};
