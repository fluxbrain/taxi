#include "NodeIdException.h"



NodeIdException::NodeIdException()
{
}


NodeIdException::~NodeIdException()
{
}

std::string NodeIdException::getError() const
{
	return std::string("NodeIdException: Bezeichner enthaelt ungueltige Zeichen");
}