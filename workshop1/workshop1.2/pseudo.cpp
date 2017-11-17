#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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
    const float pointerSpeed = 30;
}

const sf::Vector2f getNewPosition(const sf::Vector2f &mousePosition, Arrow &arrow)
{
    //get new position of arrow
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    return  delta;
};

float getNewRotation(const sf::Vector2f &deltaPosition)
{
    //get new rotation of arrow in 0..360 degrees range
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    return toDegrees(angle);
}

void setNewRotation(float &mouseRotation, Arrow &arrow)
    const float pointerRotation = pointer.getRotation();
    const float maxRotation = pointerSpeed * dt;
    float nextRotation = std::min(std::abs(mouseRotation - maxRotation), maxRotation);
    if (mouseRotation < pointerRotation)
    {
        if ((mouseRotation + 180) < pointerRotation)
        {
            arrow.setRotation(pointerRotation + nextRotation);
        }
        else
        {
            arrow.setRotation(pointerRotation - nextRotation);
        }
    }
    else
    {
        if ((mouseRotation - 180) > pointerRotation)
        {
            arrow.setRotation(pointerRotation - nextRotation);
        }
        else
        {
            arrow.setRotation(pointerRotation + nextRotation);
        }
    }
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

void update(const sf::Vector2f &mousePosition, Arrow &arrow)
{
    const sf::Vector2f deltaPosition = getNewPosition(mousePosition, arrow);
    float mouseRotation = getNewRotation(deltaPosition);
    //change arrows position and rotation
    setNewRotation(mouseRotation, arrow);
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