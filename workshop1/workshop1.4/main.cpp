#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

void initSprite(sf::Sprite &sprite, sf::Texture &texture, const std::string &fileName)
{
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
    sprite.setPosition(400, 400);
    sprite.setOrigin(16, 16);
};

sf::Vector2f getOffset(const float &deltaTime, const sf::Vector2f &motionVector)
{
    const float speed = 50;
    const float motion = hypot(motionVector.x, motionVector.y);
    if (motion > 0)
    {
        const sf::Vector2f direction = {motionVector.x / motion, motionVector.y / motion};
        const sf::Vector2f offsetPerFrame = direction * speed * deltaTime;
        if (motion < hypot(offsetPerFrame.x, offsetPerFrame.y))
        {
            return motionVector;
        }
        else
        {
            return offsetPerFrame;
        }
    }
    else
    {
        return sf::Vector2f{0, 0};
    }
};

void pollEvents(sf::RenderWindow &window, sf::Vector2f &pointerPosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            pointerPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        default:
            break;
        }
    }
}

int sign(float num)
{
    return (num >= 0) - (num < 0);
}

void update(const sf::Vector2f &pointerPosition, sf::Sprite &cat, sf::Sprite &pointer, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    const sf::Vector2f catPosition = cat.getPosition();
    const sf::Vector2f motionVector = pointerPosition - catPosition;

    cat.move(getOffset(deltaTime, motionVector));
    pointer.setPosition(pointerPosition);

    cat.setScale(sign(motionVector.x), 1);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear(sf::Color::White);
    window.draw(cat);
    window.draw(pointer);
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
        "Cat is following pointer", sf::Style::Default, settings);

    sf::Clock clock;
    sf::Vector2f pointerPosition;

    sf::Sprite cat;
    sf::Texture catTexture;
    sf::Sprite pointer;
    sf::Texture pointerTexture;
    initSprite(cat, catTexture, "cat.png");
    initSprite(pointer, pointerTexture, "red_pointer.png");

    while (window.isOpen())
    {
        pollEvents(window, pointerPosition);
        update(pointerPosition, cat, pointer, clock);
        redrawFrame(window, cat, pointer);
    };
}