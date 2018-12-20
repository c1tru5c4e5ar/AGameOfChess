#pragma once

#include<vector>
#include<utility>
#include<algorithm>

#include"ChessBoard.h"
#include"Piece.h"
#include"Player.h"

#define pii std::pair<int,int>

class Chess
{
private:

	std::vector<Piece> blackPieces;
	std::vector<Piece> whitePieces;


	void movePawn(Piece &P);
	void moveRook(Piece &P);
	void moveBishop(Piece &P);
	void moveKnight(Piece &P);
	void moveQueen(Piece &P);
	void moveKing(Piece &P);

	//Other functions to make life easier

	void placeKnight(Piece &P, int &x, int &y);
	void placeKing(Piece &P, int &x, int &y);
	void doCastle(Piece &king, Piece&rook);
	void check(Piece &king);
	//void checkMate(Piece &king);
	//void endGame();
	//use checkmate to declare winner

	//void promotePawn(Piece &P);

public:
	Chess();
	~Chess();

	ChessBoard fastboard;
	//Check valid moves for pieces
	//by making vector of all possible moves for the piece

	void generateMoves(Piece &P);
	bool movePiece(Player &player, Piece &Pfrom, Piece &Pto);
	//void highlightPiece(pii &pos);

	Piece& returnPieceAt(int posR, int posC);
	//Timer returnTimer();



};

