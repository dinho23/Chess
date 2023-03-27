#include "Rook.h"

Rook::Rook(bool type)
	: Piece(def_name, type)
{
}

bool Rook::rookHasMoved()
{
	return hasMoved;
}

void Rook::setRookHasMoved()
{
	hasMoved = true;
}

bool Rook::move(int x, int y)
{
	if (x == posX && y == posY)
		return false;

	if (x != posX && y != posY)
		return false;

	posX = x;
	posY = y;
	return true;
}
