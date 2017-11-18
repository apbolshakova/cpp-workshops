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

void initConst()
{
    const float speed = 20;
    const float offsetPerFrame = speed * deltaTime;
    const float deltaTime = clock.restart().asSeconds();
}

sf::Vector2f getNewPosition(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime, sf::Vector2f &motionVector)
{
    //TODO finish that function
    float motion = fabs(hypot(motionVector.x, motionVector.y));
    sf::Vector2f direction = {motionVector.x / motion, motionVector.y / motion};
    return std::min(motion, direction * offsetPerFrame)
};

float getNewRotation(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime, sf::Vector2f &motionVector)
{
    //TODO complete that function
    float angle = atan2(motionVector.y, motionVector.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    float mouseRotation = toDegrees(angle);
    const float pointerRotation = arrow.getRotation();
    float nextRotation = std::min(std::abs(mouseRotation - offsetPerFrame), offsetPerFrame);
    if (mouseRotation < pointerRotation)
    {
        if ((mouseRotation + 180) < pointerRotation)
        {
            return (pointerRotation + nextRotation);
        }
        else
        {
            return (pointerRotation - nextRotation);
        }
    }
    else
    {
        if ((mouseRotation - 180) > pointerRotation)
        {
            return (pointerRotation - nextRotation);
        }
        else
        {
            return (pointerRotation + nextRotation);
        }
    }
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
    sf::Vector2f motionVector = mousePosition - arrow.getPosition();
    arrow.setPosition(getNewPosition(mousePosition, arrow, deltaTime, motionVector));
    arrow.setRotation(getNewRotation(mousePosition, arrow, deltaTime, motionVector));
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
    initConst();
    while (window.isOpen())
    {
        pollEvents(window);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    };
}