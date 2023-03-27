#pragma once

#include <algorithm>
#include <vector>

#include "Piece.h"
#include "Player.h"
#include "Pawn.h"


class Board
{
protected:
	std::vector<std::vector<Piece*>> board;
	Player white;
	Player black;
	bool whitesTurn;

public:
	Board();

	void setPiecePosition();


	void takeInput();
	bool checkInput(std::string& input);
	bool checkCorrectPiece(std::string& input);
	void movePiece(int iOld, int jOld, int i, int j);


	std::vector<std::pair<int, int>> availableMoves(Piece* piece);

	std::vector<std::pair<int, int>> whitePawnMoves(Piece* piece);
	std::vector<std::pair<int, int>> blackPawnMoves(Piece* piece);

	std::vector<std::pair<int, int>> rookMoves(Piece* piece);
	std::vector<std::pair<int, int>> knightMoves(Piece* piece);
	std::vector<std::pair<int, int>> bishopMoves(Piece* piece);
	std::vector<std::pair<int, int>> kingMoves(Piece* piece);

	std::vector<std::pair<int, int>> pawnChecks(Piece* piece);

	void removeIlegalMoves(std::vector<std::pair<int,int>>& allMoves, Piece* piece);

	std::pair<int,int> inCheck();
	bool kingChecked(std::vector<std::pair<int, int>>& dangerousSquares, const std::string& type);
	bool gameOver();
	bool insufficientMaterial();

	std::pair<bool, bool> castleAvailable(Piece* piece);

	void promotePawn(Piece *piece);
	void placePiece(Piece* piece, int i, int j);

	void print();

	friend std::ostream& operator<<(std::ostream &output, const Board &board);
};

