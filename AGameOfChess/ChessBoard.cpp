#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	//Initialise Main Board
	mainBoard[0][0].assign('R', false, 0, 0);
	mainBoard[0][1].assign('N', false, 0, 1);
	mainBoard[0][2].assign('B', false, 0, 2);
	mainBoard[0][3].assign('Q', false, 0, 3);
	mainBoard[0][4].assign('K', false, 0, 4);
	mainBoard[0][5].assign('B', false, 0, 5);
	mainBoard[0][6].assign('N', false, 0, 6);
	mainBoard[0][7].assign('R', false, 0, 7);

	for (int i = 0; i < 8; ++i)
		mainBoard[1][i].assign('P', false, 1, i);

	for (int i = 2; i < 6; ++i)
		for (int j = 0; j < 8; ++j)
			mainBoard[i][j].assign('O', false, i, j);

	for (int i = 0; i < 8; ++i)
		mainBoard[6][i].assign('P', true, 6, i);

	mainBoard[7][0].assign('R', true, 7, 0);
	mainBoard[7][1].assign('N', true, 7, 1);
	mainBoard[7][2].assign('B', true, 7, 2);
	mainBoard[7][3].assign('Q', true, 7, 3);
	mainBoard[7][4].assign('K', true, 7, 4);
	mainBoard[7][5].assign('B', true, 7, 5);
	mainBoard[7][6].assign('N', true, 7, 6);
	mainBoard[7][7].assign('R', true, 7, 7);


	//Initialize Highlight Board
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			highlightBoard[i][j] = false;
}

Piece& ChessBoard::getElementOnPos(int posR, int posC)
{
	return mainBoard[posR][posC];
}

void ChessBoard::swapElements(pii &p1, pii &p2)
{
	Piece temp = mainBoard[p1.first][p1.second];
	mainBoard[p1.first][p1.second] = mainBoard[p2.first][p2.second];
	mainBoard[p2.first][p2.second] = temp;

}

void ChessBoard::moveElement(pii & p1, pii & p2)
{
	mainBoard[p2.first][p2.second] = mainBoard[p1.first][p1.second]; //Copy p1 to p2
	mainBoard[p1.first][p1.second].assign('O', false, p1.first, p1.second); //make p1 empty
}

void ChessBoard::highlightElement(pii p)
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			highlightBoard[i][j] = false;

	Piece &P = mainBoard[p.first][p.second];
	if (P.possibleMoves.empty() == true)
		return;

	for (auto it = P.possibleMoves.begin(); it != P.possibleMoves.end(); ++it)
	{
		int i = it->first;
		int j = it->second;
		highlightBoard[i][j] = true;
	}

	printhiglightBoard();
}

void ChessBoard::printmainBoard()
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::cout << mainBoard[i][j].pieceType << " ";
		}
		std::cout << std::endl;
	}
}

void ChessBoard::printhiglightBoard()
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::cout << highlightBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void ChessBoard::displaymainBoard(sf::RenderWindow &window)
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			window.draw(mainBoard[i][j].icon);
		}
	}
}



ChessBoard::~ChessBoard()
{
}
