#pragma once

#ifndef PAD_H
#define PAD_H

#include <SFML/Graphics.hpp>

#define PAD_SIZE_X 15
#define PAD_SIZE_Y 100

#define PAD_MAX_VELOCITY 5
#define PAD_NULL_VELOCITY 0

class Pad : public sf::RectangleShape
{
public:
    Pad(sf::RenderWindow* p_pMainWindow, int p_iX, int p_iY);

    // Check pad out of bounds of the given window
    bool IsPadOutOfBound(sf::RenderWindow* p_pMainWindow);

    // Pad Velocity
    int m_yVelocity;
};

#endif // PAD_H
