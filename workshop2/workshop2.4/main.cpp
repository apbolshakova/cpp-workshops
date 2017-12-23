#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cassert>
#include <random>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int BALL_SIZE = 80;

struct Ball
{
    sf::CircleShape circleShape;
    sf::Vector2f speed;
    sf::Color color;
    sf::Vector2f initPosition;
};

struct PRNG
{
    std::mt19937 engine;
};

void initBallsArray(Ball *balls, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        balls[i].circleShape.setFillColor(balls[i].color);
        balls[i].circleShape.setPosition(balls[i].initPosition);
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void handleCollisionWithWindow(Ball *balls, size_t &ballIndex, sf::Vector2f &position)
{
    if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[ballIndex].speed.x > 0))
    {
        balls[ballIndex].speed.x = -balls[ballIndex].speed.x;
    }
    if ((position.x < 0) && (balls[ballIndex].speed.x < 0))
    {
        balls[ballIndex].speed.x = -balls[ballIndex].speed.x;
    }
    if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[ballIndex].speed.y > 0))
    {
        balls[ballIndex].speed.y = -balls[ballIndex].speed.y;
    }
    if ((position.y < 0) && (balls[ballIndex].speed.y < 0))
    {
        balls[ballIndex].speed.y = -balls[ballIndex].speed.y;
    }
}

float dot(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

void handleCollisionWithBalls(Ball *balls, const size_t &ballsArraySize, size_t &ballIndex, sf::Vector2f &position)
{
    for (size_t nextBallIndex = ballIndex + 1; nextBallIndex < ballsArraySize; ++nextBallIndex)
    {
        const sf::Vector2f speedDifference = balls[ballIndex].speed - balls[nextBallIndex].speed;

        const sf::Vector2f distance = position - balls[nextBallIndex].circleShape.getPosition();
        float distanceModule = hypot(distance.x, distance.y);

        if (distanceModule < (BALL_SIZE * 2))
        {
            balls[ballIndex].speed = balls[ballIndex].speed - (dot(distance, speedDifference) * distance) / (distanceModule * distanceModule);
            balls[nextBallIndex].speed = balls[nextBallIndex].speed - (dot(-distance, -speedDifference) * -distance) / (distanceModule * distanceModule);
        }
    }
}

void update(sf::Clock &clock, Ball *balls, const size_t &ballsArraySize)
{
    const float deltaTime = clock.restart().asSeconds();
    for (size_t ballIndex = 0; ballIndex < ballsArraySize; ++ballIndex)
    {
        sf::Vector2f position = balls[ballIndex].circleShape.getPosition();

        handleCollisionWithWindow(balls, ballIndex, position);
        handleCollisionWithBalls(balls, ballsArraySize, ballIndex, position);

        position += balls[ballIndex].speed * deltaTime;
        balls[ballIndex].circleShape.setPosition(position);
    }
}

void redrawFrame(sf::RenderWindow &window, Ball *balls, size_t size)
{
    window.clear();
    for (size_t i = 0; i < size; i++)
    {
        window.draw(balls[i].circleShape);
    }
    window.display();
}

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

sf::Color mixColor(sf::Color color1, sf::Color color2)
{
    sf::Color color;
    color.r = (color1.r + color2.r) / 2;
    color.g = (color1.g + color2.g) / 2;
    color.b = (color1.b + color2.b) / 2;
    color.a = (color1.a + color2.a) / 2;
    return color;
}

int main()
{
    sf::Color colors[] = {
        {sf::Color(0, 51, 204, 255)},
        {sf::Color(0, 204, 153, 255)},
        {sf::Color(51, 51, 153, 255)},
        {sf::Color(51, 102, 255, 255)},
        {sf::Color(51, 255, 153, 255)},
        {sf::Color(102, 51, 153, 255)},
        {sf::Color(153, 0, 153, 255)},
        {sf::Color(204, 153, 255, 255)},
        {sf::Color(204, 255, 255, 255)},
        {sf::Color(204, 204, 255, 255)}};

    PRNG generator;
    initGenerator(generator);

    Ball balls[] = {
        {sf::CircleShape(BALL_SIZE), {200.f, 150.f}, mixColor(colors[random(generator, 0, std::size(colors))], colors[random(generator, 0, std::size(colors))]), {200.f, 200.f}},
        {sf::CircleShape(BALL_SIZE), {-500.f, 30.f}, mixColor(colors[random(generator, 0, std::size(colors))], colors[random(generator, 0, std::size(colors))]), {400.f, 400.f}}};

    const size_t ballsArraySize = std::size(balls);
    initBallsArray(balls, ballsArraySize);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Balls");
    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window);
        update(clock, balls, ballsArraySize);
        redrawFrame(window, balls, ballsArraySize);
    }
}