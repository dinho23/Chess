#include "pch.h"
#include "Rook.h"


Rook::Rook(bool type)
	: Piece(def_name, type),
	hasMoved {false}
{
}

bool Rook::rookHasMoved() const
{
	return hasMoved;
}

void Rook::setRookHasMoved()
{
	hasMoved = true;
}

void Rook::abstractClass() const
{
	return;
}