#include "Representation.hpp"

template <typename iterator> 
void in_cvx_hull(iterator it, circle_t circle)
{
    circle_t c = *it;
}

Representation::Representation()
{
    in_cvx_hull(circles.begin(), {});
}

void Representation::add_circle(circle_t circle) 
{
    circles.push_back(circle);
}

void Representation::cvx_hull()
{
}

void Representation::compute_implications()
{
}

void Representation::compute_cvx_geo()
{
}

