#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Representation.hpp"

struct circle_t
{
    int x;
    int y;
    int r;
};

class Editor
{
    private:
        std::vector<circle_t> circles;
    public:
        int mainloop();
        void draw_hasse();
};

#endif
