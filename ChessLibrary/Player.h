#pragma once

#include <vector>

#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"


class Player
{
protected:
	std::vector<Piece*> pieces;
	bool white;

public:
	Player(bool white);
	~Player();

	void insertPiece(Piece* piece);

	std::vector<Piece*> getPieces();
};

