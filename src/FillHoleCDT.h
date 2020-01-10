#pragma once
#include "FillHole.h"

class FillHoleCDT : public FillHole {
public:
	FillHoleCDT() = default;
	~FillHoleCDT() = default;

	void fill_hole(Polyhedron& poly, Plane& pl);
};