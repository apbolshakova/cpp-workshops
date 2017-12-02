#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct ball
{
    sf::CircleShape circleShape;
    sf::Vector2f speed;
}

int
main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int BALL_SIZE = 30;

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
        for (ball ball : balls)
        {
            sf::Vector2f position = ball.circleShape.getPosition();
            position += ball.speed * dt;

            if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (ball.speed.x > 0))
            {
                ball.speed.x = -ball.speed.x;
            }
            if ((position.x < 0) && (ball.speed.x < 0))
            {
                ball.speed.x = -ball.speed.x;
            }
            if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (ball.speed.y > 0))
            {
                ball.speed.y = -ball.speed.y;
            }
            if ((position.y < 0) && (ball.speed.y < 0))
            {
                ball.speed.y = -ball.speed.y;
            }

            ball.circleShape.setPosition(position);
        }

        window.clear();
        for (ball ball : balls)
        {
            window.draw(shape);
        }
        window.display();
    }
}