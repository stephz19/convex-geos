#include <vector>

#ifndef REPRESENTATION_H
#define REPRESENTATION_H

struct circle_t
{
    float x;
    float y;
    float r;
};

class Representation
{
    private:
    public:
        std::vector<circle_t> circles;

        Representation();

        //function types probably need to change

	void add_circle(circle_t);

        void cvx_hull();

        void compute_implications();

        void compute_cvx_geo();
};
#endif
