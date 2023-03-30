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
	int pawnMoves;
	bool lastMovePawn;

public:
	Board();

	void setPiecePosition();


	void takeInput();
	bool checkInput(std::string& input) const;
	bool checkCorrectPiece(const std::string& input);
	void movePiece(const int iOld, const int jOld, const int i, const int j);


	std::vector<std::pair<int, int>> availableMoves(Piece* piece);


	std::vector<std::pair<int, int>> whitePawnMoves(Piece* piece) const;
	std::vector<std::pair<int, int>> blackPawnMoves(Piece* piece) const;

	std::vector<std::pair<int, int>> rookMoves(Piece* piece) const;
	std::vector<std::pair<int, int>> knightMoves(Piece* piece) const;
	std::vector<std::pair<int, int>> bishopMoves(Piece* piece) const;
	std::vector<std::pair<int, int>> kingMoves(Piece* piece) const;

	std::vector<std::pair<int, int>> pawnChecks(Piece* piece) const;

	bool isIllegalMove(Piece* piece, int newI, int newJ);
	void removeIlegalMoves(std::vector<std::pair<int,int>>& allMoves, Piece* piece);
	void removeIlegalCastle(std::vector<std::pair<int, int>>& allMoves, Piece* piece);

	std::pair<int,int> inCheck() const;
	bool kingChecked(std::vector<std::pair<int, int>>& dangerousSquares, const std::string& type) const;
	bool gameOver();
	bool insufficientMaterial();

	std::pair<bool, bool> castleAvailable(Piece* piece) const;

	void promotePawn(Piece *piece);
	void placePiece(Piece* piece, const int i, const int j);

	void showAvailableMoves(const std::vector<std::pair<int, int>>& moves) const;
	void printCheck() const;
	void printTurn() const;
	void printCheckMate() const;

	void print();
};

