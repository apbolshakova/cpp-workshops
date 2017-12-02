#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

struct Ball
{
    sf::CircleShape circleShape;
    sf::Vector2f speed;
    sf::Color color;
}

/*void
initBallsArray(Ball &balls)
{
    balls.circleShape.setPosition({random(0, 800), random(0, 600)}); //height and width window
    balls.circleShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    balls.speed = {40.f, 25.f};
}*/

int
main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int BALL_SIZE = 30;

    //initBallsArray(balls);

    Ball balls[] = {
        {sf::CircleShape(30), {50.f, 15.f}, sf::Color::Red},
        {sf::CircleShape(50), {40.f, 30.f}, sf::Color::Blue}};

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Balls");
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();
        for (Ball &ball : balls)
        {
            int ballSize = ball.circleShape.getRadius();
            sf::Vector2f position = ball.circleShape.getPosition();
            position += ball.speed * deltaTime;

            if ((position.x + 2 * ballSize >= WINDOW_WIDTH) && (ball.speed.x > 0))
            {
                ball.speed.x = -ball.speed.x;
            }
            if ((position.x < 0) && (ball.speed.x < 0))
            {
                ball.speed.x = -ball.speed.x;
            }
            if ((position.y + 2 * ballSize >= WINDOW_HEIGHT) && (ball.speed.y > 0))
            {
                ball.speed.y = -ball.speed.y;
            }
            if ((position.y < 0) && (ball.speed.y < 0))
            {
                ball.speed.y = -ball.speed.y;
            }

            ball.circleShape.setFillColor(ball.color);
            ball.circleShape.setPosition(position);
        }

        window.clear();
        for (Ball &ball : balls)
        {
            window.draw(ball.circleShape);
        }
        window.display();
    }
}