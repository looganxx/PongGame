#include "ball.h"
#include "fileloader.h"

#define MIDDLE_X 400
#define MIDDLE_Y 300

Ball::Ball(sf::RenderWindow* p_pMainWindow)
{
    m_pMainWindow = p_pMainWindow;
    setRadius(25);
    setPosition(400, 300);
    setTexture(FLoader()->getBallTexture());
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
