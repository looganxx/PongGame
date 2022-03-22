#ifndef PAD_H
#define PAD_H

#include <SFML/Graphics.hpp>


class Pad : public sf::RectangleShape
{
public:
    Pad(sf::RenderWindow* p_pMainWindow, int p_iX, int p_iY);

    // Check pad out of bounds of the given window
    bool IsPadOutOfBound(sf::RenderWindow* p_pMainWindow);
};

#endif // PAD_H
