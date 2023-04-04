#include "pch.h"
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

void Rook::abstractClass()
{
	return;
}