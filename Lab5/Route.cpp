#include "Route.h"

Route::Route(Node& rSrc, Node& rDst, double dist) : Edge(rSrc, rDst), m_dist(dist)
{
}

Route::~Route()
{
}

void Route::setWeight(double dist)
{
	m_dist = dist;
}

double Route::getWeight()
{
	return m_dist;
}

