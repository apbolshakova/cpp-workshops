#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void initCatSprite(sf::Sprite &cat, sf::Texture &texture)
{
    texture.loadFromFile("cat.png");
    cat.setTexture(texture);
    cat.setPosition(200, 200);
};

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
};

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color::White);
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Cat", sf::Style::Default, settings);

    sf::Sprite cat;
    sf::Texture texture;
    initCatSprite(cat, texture);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    };
}