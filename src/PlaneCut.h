#pragma once

#include "CustomisedPolyhedron.h"

class PlaneCutter
{
public:
	PlaneCutter() = default;
	~PlaneCutter() = default;

	// Approach 1: this would modify original polyhedron
	bool cut(Polyhedron& poly_left, Polyhedron& poly_right, const Plane& pl);
	
	// Approach 2: this won't affect original polyhedron
	std::pair<Polyhedron, Polyhedron> cut(const Polyhedron& poly, const Plane& pl);
};