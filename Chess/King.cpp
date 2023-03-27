#include "King.h"

King::King(bool type)
	: Piece(def_name, type),
	hasMoved {false}
{
}

bool King::kingCastleAvailable()
{
	return !hasMoved;
}

void King::setCastleUnavailable()
{
	hasMoved = true;
}

bool King::move(int x, int y)
{
	return false;
}
