#include "pch.h"
#include "Piece.h"


Piece::Piece(const std::string& name, const bool& type)
	: m_name{ name },
	m_type{ type },
	posX{ 0 },
	posY{ 0 }
{
}

Piece::~Piece()
{
	m_name.clear();
	m_type = false;
	posX = posY = 0;
}

void Piece::setPosition(const int& x, const int& y)
{
	posX = x;
	posY = y;
}

std::pair<int, int> Piece::getPosition() const
{
	return std::pair<int, int>(posX, posY);
}

std::string Piece::getName() const
{
	return m_name;
}

std::string Piece::getShortName() const
{
	if (m_name[0] == 'K') {
		return std::string{ m_name[0],m_name[1] };
	}
	else {
		return std::string{ m_name[0] };
	}
}

bool Piece::getType() const
{
	return m_type;
}