#include "mine.h"

Mine::Mine():isMine(false), locked(true), number(0) {}

Mine& Mine::operator=(const bool& isMine)
{
	this->isMine = isMine;
	return *this;
}

Mine& Mine::operator=(const int& number)
{
	this->number = number;
	return *this;
}

void Mine::digged()
{
	locked = false;
}


