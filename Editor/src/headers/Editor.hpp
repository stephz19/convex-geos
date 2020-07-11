#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include "Representation.hpp"

class Editor
{
    private:
        Representation rep;
        sf::RenderWindow window;

    public:
        Editor();

        int mainloop();

        void draw_hasse();
};

#endif
