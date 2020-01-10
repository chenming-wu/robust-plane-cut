#include <iostream>
#include <fstream>
#include <unordered_map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Random.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>

#include "CustomisedPolyhedron.h"
#include "GeometryTools.h"
#include "FillHole.h"
#include "FillHoleCDT.h"
#include "PlaneCut.h"

#ifndef M_PI
#define M_PI 3.1415926535897
#endif

int main()
{
    std::ifstream input("fertility.off");
    Polyhedron poly;
    input >> poly;
    input.close();
    Polyhedron p_out;
    Vector3 nr(1, 0, 0);
    Plane plane(nr.x(), nr.y(), nr.z(), -2);

    PlaneCutter cutter;
    cutter.cut(poly, p_out, plane);

    FillHoleCDT holeFiller;
    holeFiller.fill_hole(poly, -nr);
	std::ofstream file_pos("poly_pos.off");
	file_pos << poly;
	file_pos.close();
    holeFiller.fill_hole(p_out, nr);

	std::ofstream file_neg("poly_neg.off");
	file_neg << p_out;
	file_neg.close();
	std::cout << "Exporting done" << std::endl;
    return -1;
}