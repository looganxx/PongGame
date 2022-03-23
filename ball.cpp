#include "ball.h"
#include "fileloader.h"


Ball::Ball(sf::RenderWindow* p_pMainWindow)
{
    m_pMainWindow = p_pMainWindow;
    setRadius(25);
    setPosition(MIDDLE_X, MIDDLE_Y);
    setTexture(FLoader()->getBallTexture());

    m_xVelocityBall = BALL_VELOCITY;
    m_yVelocityBall = BALL_VELOCITY;
}

void Ball::move()
{
    CircleShape::move(m_xVelocityBall, m_yVelocityBall);
}

void Ball::ResetPosition(void)
{
    setPosition(MIDDLE_X, MIDDLE_Y);
}

bool Ball::IsBallOutOfBound()
{
    return (getPosition().y < 0) || (getPosition().y > m_pMainWindow->getSize().y - 2*getRadius());
}


bool Ball::IsBallOutLeft()
{
    return getPosition().x < 0;
}

bool Ball::IsBallOutRight()
{
    return getPosition().x > m_pMainWindow->getSize().x - 2*getRadius();
}
