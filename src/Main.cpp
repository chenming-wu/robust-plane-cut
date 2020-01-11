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

int main(int argc, char** argv)
{
    std::ifstream input("fertility.off");
    if (argc == 5)
    {
        input.close();
        input = std::ifstream(argv[4]);
    }
    Polyhedron poly;
    input >> poly;
    input.close();
    double alpha = atof(argv[1]);
    double beta = atof(argv[2]);
    double gamma = atof(argv[3]);
	auto sphere = MinSphere(poly.points_begin(), poly.points_end());
	const auto alphaRad = alpha * 2.0 * M_PI, betaRad = beta * 2.0 * M_PI;
	const auto a = std::cos(alphaRad) * std::cos(betaRad);
	const auto b = std::sin(alphaRad) * std::cos(betaRad);
	const auto c = std::sin(betaRad);
	const auto d = 2.0 * (gamma - 0.5) * CGAL::sqrt(sphere.squared_radius());
	Vector3 planeDir(a, b, c);
	Point3 crossPnt = sphere.center() + d * planeDir;
    
    Polyhedron p_out;
    
    Plane plane(crossPnt, planeDir);
    std::cout << plane << std::endl;

    PlaneCutter cutter;
    cutter.cut_and_fill<FillHoleCDT>(poly, p_out, plane);

	std::ofstream file_pos("poly_pos.off");
	file_pos << poly;
	file_pos.close();

	std::ofstream file_neg("poly_neg.off");
	file_neg << p_out;
	file_neg.close();
	std::cout << "Exporting done" << std::endl;
    return -1;
}