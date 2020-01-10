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

#ifndef M_PI
#define M_PI 3.1415926535897
#endif
inline bool negative(Vector3& p, double C, Point3& a)
{
	Vector3 probe(a.x(), a.y(), a.z());
	return probe * p + C > 1e-8;
}

inline bool positive(Vector3& p, double C, Point3& a)
{
	Vector3 probe(a.x(), a.y(), a.z());
	return probe * p + C < -1e-8;
}
bool cut_with_plane(Polyhedron &poly, Polyhedron &poly_n, Plane plane, bool isFill)
{
    auto hole_filler = FillHoleCGAL();
    int IntrCnt = 0;
    std::vector<Edge_iterator> Edges;
    std::vector<Halfedge_handle> ModifiedEdges; //Side to be modified
    Edges.reserve(poly.size_of_halfedges() / 2);

    for (Polyhedron::Edge_iterator it = poly.edges_begin();
         it != poly.edges_end(); ++it)
    {
        Edges.push_back(it);
    }

    Vector3 cut(plane.a(), plane.b(), plane.c());
    double C = plane.d();
    cut = cut / CGAL::sqrt(cut.squared_length()); // 计算切平面的单位向量
    C = C / CGAL::sqrt(cut.squared_length());

    double d0, d1;
    for (std::vector<Polyhedron::Edge_iterator>::iterator it = Edges.begin();
         it != Edges.end(); ++it)
    {
        Halfedge_handle h = *it;
        Vector3 p1(h->prev()->vertex()->point().x(), h->prev()->vertex()->point().y(), h->prev()->vertex()->point().z());
        Vector3 p2(h->vertex()->point().x(), h->vertex()->point().y(), h->vertex()->point().z());
        d0 = cut * p1 + C;
        d1 = cut * p2 + C;
        Vector3 Q;
        if ((d0 >= 0 && d1 < 0) || (d0 < 0 && d1 >= 0))
        {
            IntrCnt++;
            Q = p1 + ((d0 / (d0 - d1)) * (p2 - p1));
            Halfedge_handle t = poly.split_edge(h);
            Point3 new_p(Q.x(), Q.y(), Q.z());
            t->vertex()->point() = new_p;
            ModifiedEdges.push_back(t);
        }
    }

    std::cout << "ModifiedEdges: " << ModifiedEdges.size() << std::endl;

    // stitch model
    for (std::vector<Halfedge_handle>::iterator it = ModifiedEdges.begin();
         it != ModifiedEdges.end(); it++)
    {
        Halfedge_handle h = *it;
        Halfedge_handle g = h->opposite()->prev();
        Facet_handle f_h = h->facet();
        Facet_handle g_h = g->facet();
        Halfedge_handle tmp_he;
        if (f_h != nullptr && !f_h->is_triangle())
        {
            if (f_h->is_quad())
            {
                tmp_he = poly.split_facet(h, h->next()->next());
            }
            else
            {
                tmp_he = poly.split_facet(h, h->next()->next());
                poly.split_facet(h, h->next()->next());
            }
        }

        if (g_h != nullptr && !g_h->is_triangle())
        {
            if (g_h->is_quad())
            {
                tmp_he = poly.split_facet(g, g->next()->next());
            }
            else
            {
                tmp_he = poly.split_facet(g, g->next()->next());
                poly.split_facet(g, g->next()->next());
            }
        }
    }

    //return true;

    poly_n = poly;

    for (Facet_iterator it = poly.facets_begin(), nd = poly.facets_end();
         it != nd;)
    {
        Facet_iterator itNext = it;
        ++itNext;
        Halfedge_handle h = it->halfedge();
        if (h == NULL)
        {
            it = itNext;
            continue;
        }
        Halfedge_handle e = h;
        do
        {
            if (positive(cut, C, h->vertex()->point()))
            {
                poly.erase_facet(e);
                break;
            }
            h = h->next();
        } while (h != e);
        it = itNext;
    }

    for (Facet_iterator it = poly_n.facets_begin(), nd = poly_n.facets_end();
         it != nd;)
    {
        Facet_iterator itNext = it;
        ++itNext;
        Halfedge_handle h = it->halfedge();
        if (h == NULL)
        {
            it = itNext;
            continue;
        }
        Halfedge_handle e = h;
        do
        {
            if (negative(cut, C, h->vertex()->point()))
            {
                poly_n.erase_facet(e);
                break;
            }
            h = h->next();
        } while (h != e);
        it = itNext;
    }

    std::cout << "Cutting done" << std::endl;
    if (isFill)
    {
        hole_filler.fill_hole(poly, plane);
        std::ofstream file_pos("poly_pos.off");
        file_pos << poly;
        file_pos.close();
        hole_filler.fill_hole(poly_n, plane);
        std::ofstream file_neg("poly_neg.off");
        file_neg << poly_n;
        file_neg.close();
        std::cout << "Exporting done" << std::endl;
    }
    return true;
}

int main()
{
    std::ifstream input("input.off");
    Polyhedron poly;
    input >> poly;
    input.close();
    Polyhedron p_out;
    cut_with_plane(poly, p_out, Plane(0, 1, 0, -5), true);
    return -1;
}