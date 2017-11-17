#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <algorithm>

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({400, 300});

    arrow.setPointCount(7);
    arrow.setPoint(0, {60, 0});
    arrow.setPoint(1, {0, 70});
    arrow.setPoint(2, {0, 30});
    arrow.setPoint(3, {-60, 30});
    arrow.setPoint(4, {-60, -30});
    arrow.setPoint(5, {0, -30});
    arrow.setPoint(6, {0, -70});

    arrow.setFillColor(sf::Color::Yellow);

    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(3);
};

sf::Vector2f getNewPosition(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime)
{
    //TODO finish that function
    const float speed = 20;
    sf::Vector2f motionVector = mousePosition - arrow.getPosition();
    float motion = fabs(hypot(motionVector.x, motionVector.y));
    sf::Vector2f direction = {motionVector.x / motion, motionVector.y / motion};
    float offsetPerFrame = speed * deltaTime;
    return std::min(motion, direction * offsetPerFrame)
};

float getNewRotation(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime)
{
    //TODO complete that function
    return 0;
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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    arrow.setPosition(getNewPosition(mousePosition, arrow, deltaTime));
    arrow.setRotation(getNewRotation(mousePosition, arrow, deltaTime));
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color::White);
    window.draw(arrow);
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
        "Arrow", sf::Style::Default, settings);

    sf::Clock clock;
    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    };
}