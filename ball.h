#pragma once

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

#define MIDDLE_X 400
#define MIDDLE_Y 300
#define BALL_RADIUS 25
#define BALL_VELOCITY 4

class Ball : public sf::CircleShape
{
public:
    Ball(sf::RenderWindow* p_pMainWindow);

    virtual void move();

    void ResetPosition(void);

    bool IsBallOutOfBound();

    bool IsBallOutLeft();

    bool IsBallOutRight();

    // ball velocity
    int m_xVelocityBall;
    int m_yVelocityBall;

private:
    sf::RenderWindow* m_pMainWindow;
};

#endif // BALL_H
