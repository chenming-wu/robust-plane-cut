#pragma once
#include "FillHole.h"

class FillHoleCueMol : public FillHole {
public:
	FillHoleCueMol() = default;
	~FillHoleCueMol() = default;

	void fill_hole(Polyhedron& poly, Plane& pl);
};