#include "Chess.h"

Chess::Chess()
{

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 8; ++j) {
			generateMoves(fastboard.getElementOnPos(i, j));
			blackPieces.push_back(fastboard.getElementOnPos(i, j));
		}
	}

	for (int i = 6; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			generateMoves(fastboard.getElementOnPos(i, j));
			whitePieces.push_back(fastboard.getElementOnPos(i, j));
		}
	}

}

Chess::~Chess()
{
}

void Chess::generateMoves(Piece &P)
{
	if (P.pieceType == 'P') {
		movePawn(P);
	}
	else if (P.pieceType == 'R') {
		moveRook(P);
	}
	else if (P.pieceType == 'B') {
		moveBishop(P);
	}
	else if (P.pieceType == 'N') {
		moveKnight(P);
	}
	else if (P.pieceType == 'K') {
		moveKing(P);
	}
	else if (P.pieceType == 'Q') {
		moveQueen(P);
	}
}

bool Chess::movePiece(Player &player, Piece &Pfrom, Piece &Pto)
{
	//check iff Pto.piecePos is a possible move for Pfrom
	if (std::find(Pfrom.possibleMoves.begin(), Pfrom.possibleMoves.end(), Pto.piecePos) != Pfrom.possibleMoves.end())
	{
		Pfrom.possibleMoves.clear();

		Piece temp = Pfrom;
		//If target is empty
		if (Pto.pieceType == 'O')
		{

			pii ptempfrom = Pfrom.piecePos;
			pii ptempto = Pto.piecePos;

			pii temp = Pfrom.piecePos;
			Pfrom.piecePos = Pto.piecePos;
			Pto.piecePos = temp;

			fastboard.swapElements(ptempfrom, ptempto);
			generateMoves(Pfrom);
			generateMoves(Pto);
		}

		//If target has enemy piece
		else
		{
			Pto.isCaptured = true;
			player.capturedPieces.push_back(Pto);

			pii ptempfrom, ptempto;
			ptempfrom = Pfrom.piecePos;
			ptempto = Pto.piecePos;

			Pfrom.piecePos = Pto.piecePos;
			fastboard.moveElement(Pfrom.piecePos, Pto.piecePos);
			generateMoves(Pfrom);
			generateMoves(Pto);

		}

		Pfrom.isFirstMove = false;

		//Update WhitePieces/BlackPieces array;
		std::vector<Piece>::iterator first, last;
		if (Pfrom.pieceColor == true)
		{
			first = whitePieces.begin();
			last = whitePieces.end();
		}
		else
		{
			first = blackPieces.begin();
			last = blackPieces.end();
		}
		//Look for element in array
		for (auto it = first; it != last; ++it)
		{
			//Operator Overload
			if (temp.isEqual(*it))
				*it = Pfrom; //Update element
		}
		return true;
	}
	return false;
}

Piece &Chess::returnPieceAt(int posR, int posC)
{
	return fastboard.getElementOnPos(posR, posC);
}



void Chess::moveQueen(Piece &P)
{
	//Vertically:Up 
	for (int i = P.piecePos.first - 1; i >= 0 && i < 8; --i)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, P.piecePos.second);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) { //If a piece of opposite color is present
				P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second)); //Piece can be captured, add to list of possible moves
				break; //Cannot move further
			}
			else
				break; //If piece of same color is present, cannot move further
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second)); //Add to list of possible moves
	}

	//Vertically:Down
	for (int i = P.piecePos.first + 1; i >= 0 && i < 8; ++i)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, P.piecePos.second);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second));
	}

	//Horizontally:Left
	for (int j = P.piecePos.second - 1; j >= 0 && j < 8; --j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(P.piecePos.first, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
	}

	//Horizontally:Right
	for (int j = P.piecePos.second + 1; j >= 0 && j < 8; ++j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(P.piecePos.first, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
	}

	//Diagonally:Down Right
	for (int i = P.piecePos.first + 1, j = P.piecePos.second + 1; i >= 0 && i < 8 && j >= 0 && j < 8; ++i, ++j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Up Right
	for (int i = P.piecePos.first - 1, j = P.piecePos.second + 1; i >= 0 && i < 8 && j >= 0 && j < 8; --i, ++j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Up Left
	for (int i = P.piecePos.first - 1, j = P.piecePos.second - 1; i >= 0 && i < 8 && j >= 0 && j < 8; --i, --j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Down Left
	for (int i = P.piecePos.first + 1, j = P.piecePos.second - 1; i >= 0 && i < 8 && j >= 0 && j < 8; ++i, --j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}
}

void Chess::moveKing(Piece &P)
{
	int posR, posC;

	posR = P.piecePos.first + 1;
	posC = P.piecePos.second + 1;
	placeKing(P, posR, posC);

	posR = P.piecePos.first + 1;
	posC = P.piecePos.second - 1;
	placeKing(P, posR, posC);

	posR = P.piecePos.first - 1;
	posC = P.piecePos.second + 1;
	placeKing(P, posR, posC);

	posR = P.piecePos.first - 1;
	posC = P.piecePos.second - 1;
	placeKing(P, posR, posC);

	posR = P.piecePos.first + 1;
	posC = P.piecePos.second;
	placeKing(P, posR, posC);

	posR = P.piecePos.first - 1;
	posC = P.piecePos.second;
	placeKing(P, posR, posC);

	posR = P.piecePos.first;
	posC = P.piecePos.second + 1;
	placeKing(P, posR, posC);

	posR = P.piecePos.first;
	posC = P.piecePos.second - 1;
	placeKing(P, posR, posC);

	//Castling
	doCastle(P, fastboard.getElementOnPos(P.piecePos.first, P.piecePos.second + 3));
	doCastle(P, fastboard.getElementOnPos(P.piecePos.first, P.piecePos.second - 4));

	//Check for checkmate
	//if (P.isinCheck == true && P.possibleMoves.size() == 0)
		//checkMate(P);

}

void Chess::moveBishop(Piece &P)
{
	//Diagonally:Down Right
	for (int i = P.piecePos.first + 1, j = P.piecePos.second + 1; i >= 0 && i < 8 && j >= 0 && j < 8; ++i, ++j)
	{
		Piece& tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Up Right
	for (int i = P.piecePos.first - 1, j = P.piecePos.second + 1; i >= 0 && i < 8 && j >= 0 && j < 8; --i, ++j)
	{
		Piece tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Up Left
	for (int i = P.piecePos.first - 1, j = P.piecePos.second - 1; i >= 0 && i < 8 && j >= 0 && j < 8; --i, --j)
	{
		Piece tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}

	//Diagonally:Down Left
	for (int i = P.piecePos.first + 1, j = P.piecePos.second - 1; i >= 0 && i < 8 && j >= 0 && j < 8; ++i, --j)
	{
		Piece tempPiece = fastboard.getElementOnPos(i, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, j));
	}
}

void Chess::movePawn(Piece &P)
{
	int movementDirection = 1;
	if (P.pieceColor == true)
		movementDirection = -1;


	int nextPos = P.piecePos.first + movementDirection;

	if (nextPos >= 0 && nextPos < 8) {
		//Move one square
		Piece& tempPiece1 = fastboard.getElementOnPos(nextPos, P.piecePos.second);
		if (tempPiece1.pieceType == 'O')
		{
			P.possibleMoves.push_back(std::make_pair(nextPos, P.piecePos.second));
		}
	}


	if (P.isFirstMove == true)
	{
		//Move two squares
		nextPos = P.piecePos.first + (2 * movementDirection);
		Piece& tempPiece2 = fastboard.getElementOnPos(nextPos, P.piecePos.second);

		if (tempPiece2.pieceType == 'O')
		{
			P.possibleMoves.push_back(std::make_pair(nextPos, P.piecePos.second));
		}
		P.isFirstMove = false;
	}

	//If pawn moves two squares
	//En Passant is possible;

	//Check capture, diagnonally 
	Piece& tempPiece3 = fastboard.getElementOnPos(P.piecePos.first + movementDirection, P.piecePos.second + 1);
	if (tempPiece3.pieceType != 'O' && tempPiece3.pieceColor != P.pieceColor)
		P.possibleMoves.push_back(std::make_pair(P.piecePos.first + movementDirection, P.piecePos.second + 1));

	Piece& tempPiece4 = fastboard.getElementOnPos(P.piecePos.first + movementDirection, P.piecePos.second - 1);
	if (tempPiece4.pieceType != 'O' && tempPiece4.pieceColor != P.pieceColor)
		P.possibleMoves.push_back(std::make_pair(P.piecePos.first + movementDirection, P.piecePos.second - 1));

	//Check enPassant: "capture in passing"


	//Check promotion:
	//if(P.piecePos.first == 0 || P.piecePos.first == 7)
	//		promotePawn(P);


}

void Chess::moveRook(Piece &P)
{
	//Vertically:Up 
	for (int i = P.piecePos.first - 1; i >= 0 && i < 8; --i)
	{
		Piece tempPiece = fastboard.getElementOnPos(i, P.piecePos.second);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) { //If a piece of opposite color is present
				P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second)); //Piece can be captured, add to list of possible moves
				break; //Cannot move further
			}
			else
				break; //If piece of same color is present, cannot move further
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second)); //Add to list of possible moves
	}

	//Vertically:Down
	for (int i = P.piecePos.first + 1; i >= 0 && i < 8; ++i)
	{
		Piece tempPiece = fastboard.getElementOnPos(i, P.piecePos.second);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(i, P.piecePos.second));
	}

	//Horizontally:Left
	for (int j = P.piecePos.second - 1; j >= 0 && j < 8; --j)
	{
		Piece tempPiece = fastboard.getElementOnPos(P.piecePos.first, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
	}

	//Horizontally:Right
	for (int j = P.piecePos.second + 1; j >= 0 && j < 8; ++j)
	{
		Piece tempPiece = fastboard.getElementOnPos(P.piecePos.first, j);
		if (tempPiece.pieceType != 'O') {
			if (tempPiece.pieceColor != P.pieceColor) {
				P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
				break;
			}
			else
				break;
		}
		else
			P.possibleMoves.push_back(std::make_pair(P.piecePos.first, j));
	}

	//Castling

}

void Chess::placeKnight(Piece &P, int &x, int &y)
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		Piece temp = fastboard.getElementOnPos(x, y);
		if (temp.pieceType == 'O' || temp.pieceColor != P.pieceColor) {
			P.possibleMoves.push_back(std::make_pair(x, y));
		}
	}

}

void Chess::moveKnight(Piece &P)
{
	int posR, posC;

	posR = P.piecePos.first + 2;
	posC = P.piecePos.second + 1;
	placeKnight(P, posR, posC);


	posR = P.piecePos.first + 2;
	posC = P.piecePos.second - 1;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first - 2;
	posC = P.piecePos.second + 1;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first - 2;
	posC = P.piecePos.second - 1;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first + 1;
	posC = P.piecePos.second + 2;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first - 1;
	posC = P.piecePos.second + 2;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first + 1;
	posC = P.piecePos.second - 2;
	placeKnight(P, posR, posC);

	posR = P.piecePos.first - 1;
	posC = P.piecePos.second - 2;
	placeKnight(P, posR, posC);
}

void Chess::placeKing(Piece &P, int &x, int &y)
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		Piece temp = fastboard.getElementOnPos(x, y);
		if (temp.pieceType == 'O' || temp.pieceColor != P.pieceColor) {
			P.possibleMoves.push_back(std::make_pair(x, y));
		}
	}
}

void Chess::doCastle(Piece &king, Piece &rook)
{
	/*
	However, in order to castle, the following conditions must be met:

	it must be that king's very first move
	it must be that rook's very first move
	there cannot be any pieces between the king and rook to move
	the king may not be in check or pass through check

	Notice that when you castle one direction the king is closer to the side of the board. That is called castling "kingside". Castling to the other side, through where the queen sat, is called castling "queenside". Regardless of which side, the king always moves only two squares when castling.
	*/
	if (king.isFirstMove == true && rook.isFirstMove == true && king.isinCheck == false)
	{
		bool pieceInBetweenRK = false;
		if (rook.piecePos.second == 7)
		{
			for (int col = king.piecePos.second + 1; col < 7; ++col)
			{
				Piece p = fastboard.getElementOnPos(king.piecePos.first, col);
				if (p.pieceType != 'O')
				{
					pieceInBetweenRK = true;
					break;
					rook.iscastlingPossible = false;
				}
			}
			if (pieceInBetweenRK == false)
			{
				king.possibleMoves.push_back(std::make_pair(king.piecePos.first, king.piecePos.second + 2));
				rook.possibleMoves.push_back(std::make_pair(rook.piecePos.first, rook.piecePos.second - 2));
			}
		}
		else
		{
			for (int col = king.piecePos.second - 1; col > 0; --col)
			{
				Piece p = fastboard.getElementOnPos(king.piecePos.first, col);
				if (p.pieceType != 'O')
				{
					pieceInBetweenRK = true;
					break;
					rook.iscastlingPossible = false;
				}
			}

			if (pieceInBetweenRK == false)
			{
				king.possibleMoves.push_back(std::make_pair(king.piecePos.first, king.piecePos.second - 2));
				rook.possibleMoves.push_back(std::make_pair(rook.piecePos.first, rook.piecePos.second + 3));
			}
		}

	}
}

void Chess::check(Piece & king)
{
	if (king.isinCheck == true)
		king.isinCheck = false;

	std::vector<Piece>::iterator first, last;
	if (king.pieceColor == true)
	{
		first = blackPieces.begin();
		last = blackPieces.end();
	}
	else
	{
		first = whitePieces.begin();
		last = whitePieces.end();
	}

	for (auto it = first; it != last; ++it) {
		Piece &p = *it;
		for (unsigned int i = 0; i < p.possibleMoves.size(); ++i) {
			if (p.possibleMoves.at(i) == king.piecePos)
				king.isinCheck = true; return;
		}
	}

}


