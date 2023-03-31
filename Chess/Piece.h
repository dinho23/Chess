#pragma once

#include <iostream>
#include <string>


class Piece
{
	
protected:
	std::string m_name;
	bool m_type;
	int posX, posY;

public:
	Piece(const std::string &name, const bool &type);

	void setPosition(const int& x, const int& y);
	std::pair<int,int> getPosition();

	std::string getName() const;
	std::string getShortName() const;
	
	bool getType() const;
	
	virtual void abstractClass() = 0;

	friend std::ostream& operator<<(std::ostream& output, const Piece& piece);
};