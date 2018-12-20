#include "Player.h"

Player::Player()
{
	playerColor = false;
	playerName = "Empty";
}

Player::Player(std::string name, bool color)
{
	playerColor = color;
	playerName = name;
}

Player::~Player()
{
}
