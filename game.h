#pragma once

#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "pad.h"

class Game
{
public:
    Game();

    void StartGame();

private:
    ///Main Window
    sf::RenderWindow* m_pMainWindow;

    /// Ball of the game
    Ball *m_pBall;

    /// Left Pad
    Pad *m_pPad1;

    /// Right Pad
    Pad *m_pPad2;
};

#endif // GAME_H
