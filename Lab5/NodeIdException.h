#pragma once
#include <string>

class NodeIdException
{
public:
	NodeIdException();
	~NodeIdException();

	std::string getError() const;
};

