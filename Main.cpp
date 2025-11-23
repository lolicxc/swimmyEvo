#include <SFML/Graphics.hpp>

int main()
{
    const int width = 1080;
    const int height = 720;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML works!");
    sf::RectangleShape shape({ 100, 100 });
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ width / 2, height / 2 });
 /*   shape.setOrigin(shape.getGeometricCenter());*/
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed-> scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}