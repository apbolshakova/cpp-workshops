#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
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

sf::Vector2f getOffset(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, const float &deltaTime, const sf::Vector2f &motionVector)
{
    const float speed = 20;
    const float motion = fabs(hypot(motionVector.x, motionVector.y));
    if (motion > 0)
    {
        const sf::Vector2f direction = {motionVector.x / motion, motionVector.y / motion};
        const sf::Vector2f offsetPerFrame = direction * speed * deltaTime;
        if (motion < fabs(hypot(offsetPerFrame.x, offsetPerFrame.y)))
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

float toDegrees(float radians)
{
    float result = double(radians) * 180.0 / M_PI;
    if (result < 0)
    {
        result = 360 + result;
    }
    return result;
}

float getNewRotation(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, const float &deltaTime, const sf::Vector2f &motionVector)
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

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x),
                     float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
        default:
            break;
        }
    }
};

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, sf::Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();
    const sf::Vector2f arrowPosition = arrow.getPosition();
    const sf::Vector2f motionVector = mousePosition - arrowPosition;
    arrow.move(getOffset(mousePosition, arrow, deltaTime, motionVector));
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
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    };
}