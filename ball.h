#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>


class Ball : public sf::CircleShape
{
public:
    Ball(sf::RenderWindow* p_pMainWindow);

    bool IsBallOutOfBound();

    bool IsBallOutLeft();

    bool IsBallOutRight();

private:
    sf::RenderWindow* m_pMainWindow;
};

#endif // BALL_H
