#include "Piece.h"

Piece::Piece()
{
	//Unassigned Piece
	pieceType = 'U';
	pieceColor = false;
	piecePos = std::make_pair(0, 0);
	isFirstMove = false;
	iscastlingPossible = false;
	isEnPassantPossible = false;
	ispromotionPossible = false;
	isinCheck = false;
}

void Piece::assign(char pType, bool pCol, int piecePosR, int piecePosC)
{
	pieceType = pType;
	pieceColor = pCol;

	piecePos = std::make_pair(piecePosR, piecePosC);

	isFirstMove = true;

	/*
	//Special Moves
	if(pType == 'K' || pType == 'R')
		iscastlingPossible = true; //if rook or king, 1
	else
		iscastlingPossible = false;

	if (pType == 'P') {
		isEnPassantPossible = true; //if pawn, 1
		ispromotionPossible = false;
	}
	*/

	//Load Icon for respective piece
	void loadIcon();
	void setPos();
}

bool Piece::isEqual(Piece & P)
{
	if (pieceColor == P.pieceColor && pieceType == P.pieceType && piecePos == P.piecePos)
		return true;
}

void Piece::loadIcon()
{
	std::string filename, color;

	if (pieceColor == true)
		color = "White";
	else
		color = "Black";


	if (pieceType == 'P') {
		filename = "Pawn";
	}
	else if (pieceType == 'R') {
		filename = "Rook";
	}
	else if (pieceType == 'B') {
		filename = "Bishop";
	}
	else if (pieceType == 'N') {
		filename = "Knight";
	}
	else if (pieceType == 'K') {
		filename = "King";
	}
	else if (pieceType == 'Q') {
		filename = "Queen";
	}
	else if (pieceType == 'O') {
		filename = "Empty";
	}

	std::cout << color + filename;

	if (!image.loadFromFile(color + filename))
		std::cerr << "Unable to load pieceIcon for " << color + filename << std::endl;
	icon.setTexture(image);

}

void Piece::setPos()
{
	Ox = 160.f + (piecePos.first * 100);
	Oy = 140.f + (piecePos.second * 100);

	sf::FloatRect dimentions = icon.getLocalBounds();

	icon.setOrigin(dimentions.width / 2, dimentions.height / 2);
	icon.setPosition(Ox, Oy);
}

Piece::~Piece()
{
}