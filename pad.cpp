#include "pad.h"

#include "fileloader.h"

Pad::Pad(sf::RenderWindow* p_pMainWindow, int p_iX, int p_iY)
{
    setSize(sf::Vector2f(30, 100));
    setPosition(p_iX, p_iY);
    setTexture(FLoader()->getPadTexture());
}


bool Pad::IsPadOutOfBound(sf::RenderWindow* p_pMainWindow)
{
    return (getPosition().y < 0) || (getPosition().y > p_pMainWindow->getSize().y - getSize().y);
}
