#pragma once

#include "CustomisedPolyhedron.h"

class FillHole
{
public:
	FillHole() = default;
	~FillHole() = default;

	virtual void fill_hole(Polyhedron& poly, Plane& pl) = 0;
};

class FillHoleCGAL : public FillHole
{
public:
	FillHoleCGAL() = default;
	~FillHoleCGAL() = default;

	void fill_hole(Polyhedron& poly, Plane& pl);
};
