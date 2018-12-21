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
	loadIcon();
	setPos();
}

bool Piece::isEqual(Piece & P)
{
	if (pieceColor == P.pieceColor && pieceType == P.pieceType && piecePos == P.piecePos)
		return true;
}

void Piece::loadIcon()
{
	std::string piecename, color;

	if (pieceColor == true)
		color = "White";
	else
		color = "Black";

	if (pieceType == 'P') {
		piecename = "Pawn";
	}
	else if (pieceType == 'R') {
		piecename = "Rook";
	}
	else if (pieceType == 'B') {
		piecename = "Bishop";
	}
	else if (pieceType == 'N') {
		piecename = "Knight";
	}
	else if (pieceType == 'K') {
		piecename = "King";
	}
	else if (pieceType == 'Q') {
		piecename = "Queen";
	}
	else if (pieceType == 'O') {
		piecename = "Empty";
	}


	std::string filename = "pieces/" + color + piecename + ".png";
	std::cout << filename;

	if (!image.loadFromFile(filename))
		std::cerr << "Unable to load pieceIcon for " << filename << std::endl;
	icon.setTexture(image);

}

void Piece::setPos()
{
	Ox = 210.f + (piecePos.second * 100);
	Oy = 190.f + (piecePos.first * 100);

	sf::FloatRect dimentions = icon.getLocalBounds();
	std::cout << dimentions.width;
	icon.setOrigin((dimentions.width/2), (dimentions.height/2));

	icon.setPosition(Ox, Oy);
}

Piece::~Piece()
{
}