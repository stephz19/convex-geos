#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>
#include "Editor.hpp"

# define M_PI 3.14159265358979323846  /* pi */
# define TITLE "Convex Geometry Editor"

using namespace std;

Editor::Editor() : 
    window(sf::VideoMode::getDesktopMode(), TITLE)
{
    // Lorem Ipsum
    rep.circles.push_back((circle_t) {300.f, 225.f, 100.f});
    rep.circles.push_back((circle_t) {300.f, 200.f, 150.f});
    rep.circles.push_back((circle_t) {300.f, 300.f, 200.f});
}

int Editor::mainloop()
{
    float thickness = 2.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for(vector<circle_t>::iterator it = rep.circles.begin();
                it != rep.circles.end();
                it++)
        {
            size_t resolution = M_PI * it->r;
            sf::CircleShape circ(it->r, resolution);
            circ.setOutlineThickness(thickness);
            circ.setOutlineColor(sf::Color::Black);
            circ.setFillColor(sf::Color::Transparent);
            // position based on top left of bounding box, so subtract radius
            circ.setPosition(it->x - it->r, it->y - it->r);
            window.draw(circ);
        }
        window.display();
    }

    return 0;
};
