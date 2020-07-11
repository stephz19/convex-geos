#include "Editor.hpp"

Editor::Editor()
{
}

int Editor::mainloop()
{
    int win_width = 200;
    int win_height = 600;
    const char* title = "Placeholder";
    //sf::RenderWindow window(sf::VideoMode(win_width, win_height), title);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), title);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};
