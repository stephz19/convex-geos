#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Representation.hpp"

class Editor
{
    private:
        Representation circles;
    public:
        int mainloop();

        void draw_hasse();
};

#endif
