#pragma once
#include "Edge.h"
class Route :
	public Edge
{
public:
	Route(Node& rSrc, Node& rDst, double dist);
	virtual ~Route();

	void setWeight(double dist);

	double getWeight() override;


private:
	double m_dist = DBL_MAX;
};

