#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include "Representation.hpp"

class Editor
{
    private:
        Representation circles;

    public:
        Editor();

        int mainloop();

        void draw_hasse();
};

#endif
