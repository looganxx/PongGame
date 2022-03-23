#include "game.h"
#include "fileloader.h"
#include <iostream>
#include <sstream>

#define WINDOW_X 800
#define WINDOW_Y 600

Game::Game()
{
    // file includes
    if(FLoader()->LoadAllFile() == false)
    {
        return;
    }

    // Window
    m_pMainWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_X,WINDOW_Y), "Pong Game");
    m_pMainWindow->setFramerateLimit(60);
    m_pMainWindow->setKeyRepeatEnabled(false);

    sf::VideoMode l_Desktop = sf::VideoMode::getDesktopMode();
    m_pMainWindow->setPosition(sf::Vector2i(l_Desktop.width/2 - m_pMainWindow->getSize().x/2, l_Desktop.height/2 - m_pMainWindow->getSize().y/2));

    // Pad1
    m_pPad1 = new Pad(m_pMainWindow, 50, 200);

    // Pad2
    m_pPad2 = new Pad(m_pMainWindow, 720, 200);

    // Ball
    m_pBall = new Ball(m_pMainWindow);
}

void Game::StartGame()
{
    // Variable
    bool l_boPlay = true;

    // Event
    sf::Event l_Event;

    // Score Text
    sf::Text l_Score;
    l_Score.setFont(*(FLoader()->getFont()));
    l_Score.setCharacterSize(35);
    l_Score.setFillColor(sf::Color::Red);
    l_Score.setPosition(m_pMainWindow->getSize().x/2 - 30 , 20);

    sf::Sound l_HitSound;
    l_HitSound.setBuffer(*(FLoader()->getHitSoundsBuffer()));

    //////////////// Shapes /////////////////
    // Background
    sf::RectangleShape l_Background;
    l_Background.setSize(sf::Vector2f(WINDOW_X, WINDOW_Y));
    l_Background.setPosition(0, 0);
    l_Background.setTexture(FLoader()->getBackgroundTexture());

    //////////////////////////////////////////

    // States
    bool l_boLeftUp = false, l_boLeftDown = false; // for Pad1
    bool l_boRightUp = false, l_boRightDown = false; // for Pad2

    // Variable
    int l_pPad1Score = 0, l_Pad2Score = 0;

    while(l_boPlay == true)
    {
        // EVENTS
        while(m_pMainWindow->pollEvent(l_Event))
        {
            // KeyPressed
            if(l_Event.type == sf::Event::KeyPressed)
            {
                if(l_Event.key.code == sf::Keyboard::W)
                {
                    l_boLeftUp = true;
                }
                if(l_Event.key.code == sf::Keyboard::S)
                {
                    l_boLeftDown = true;
                }
                if(l_Event.key.code == sf::Keyboard::Up)
                {
                    l_boRightUp = true;
                }
                if(l_Event.key.code == sf::Keyboard::Down)
                {
                    l_boRightDown = true;
                }
            }

            // KeyReleased
            if(l_Event.type == sf::Event::KeyReleased)
            {
                if(l_Event.key.code == sf::Keyboard::W)
                {
                    l_boLeftUp = false;
                }
                if(l_Event.key.code == sf::Keyboard::S)
                {
                    l_boLeftDown = false;
                }
                if(l_Event.key.code == sf::Keyboard::Up)
                {
                    l_boRightUp = false;
                }
                if(l_Event.key.code == sf::Keyboard::Down)
                {
                    l_boRightDown = false;
                }
            }

            // Close window event
            if(l_Event.type == sf::Event::Closed)
            {
                l_boPlay = false;
            }
        }

        // LOGIC

        // Pad1 move
        if(l_boLeftUp == true)
        {
            m_pPad1->m_yVelocity = -PAD_MAX_VELOCITY;
        }

        if(l_boLeftDown == true)
        {
            m_pPad1->m_yVelocity = PAD_MAX_VELOCITY;
        }

        // Do not move the pad
        if(l_boLeftUp == l_boLeftDown)
        {
            m_pPad1->m_yVelocity = PAD_NULL_VELOCITY;
        }

        m_pPad1->move(PAD_NULL_VELOCITY, m_pPad1->m_yVelocity);

        // check pad out of bounds
        if(m_pPad1->IsPadOutOfBound(m_pMainWindow) == true)
        {
            m_pPad1->move(PAD_NULL_VELOCITY, -m_pPad1->m_yVelocity);
        }

        // Pad2 move
        if(l_boRightUp == true)
        {
            m_pPad2->m_yVelocity = -PAD_MAX_VELOCITY;
        }

        if(l_boRightDown == true)
        {
            m_pPad2->m_yVelocity = PAD_MAX_VELOCITY;
        }

        // Do not move the pad
        if(l_boRightUp == l_boRightDown)
        {
            m_pPad2->m_yVelocity = PAD_NULL_VELOCITY;
        }

        m_pPad2->move(PAD_NULL_VELOCITY, m_pPad2->m_yVelocity);

        // check pad out of bounds
        if(m_pPad2->IsPadOutOfBound(m_pMainWindow) == true)
        {
            m_pPad2->move(PAD_NULL_VELOCITY, -m_pPad2->m_yVelocity);
        }


        // Ball
        m_pBall->move();

        // check ball out of bounds
        if(m_pBall->IsBallOutOfBound() == true)
        {
            m_pBall->m_yVelocityBall =  - m_pBall->m_yVelocityBall;
            m_pBall->move();
        }

        // Score for pad 2
        if(m_pBall->IsBallOutLeft() == true)
        {
            l_Pad2Score++;
            m_pBall->ResetPosition();
        }

        // Score for pad 1
        if(m_pBall->IsBallOutRight() == true)
        {
            l_pPad1Score++;
            m_pBall->ResetPosition();
        }

        sf::FloatRect l_tempRect(m_pPad1->getGlobalBounds());
        sf::FloatRect l_intersectRect(l_tempRect.left + l_tempRect.width,
                                      l_tempRect.top,
                                      0.01,
                                      l_tempRect.height);

        if(m_pBall->getGlobalBounds().intersects(l_intersectRect) == true)
        {
            l_HitSound.play();

            m_pBall->m_xVelocityBall =  - m_pBall->m_xVelocityBall;
            m_pBall->move();
        }


        if(m_pBall->getGlobalBounds().intersects(m_pPad2->getGlobalBounds()) == true)
        {
            l_HitSound.play();

            m_pBall->m_xVelocityBall =  - m_pBall->m_xVelocityBall;

            m_pBall->move();
        }

        // RENDERING
        m_pMainWindow->clear();

        m_pMainWindow->draw(l_Background);
        m_pMainWindow->draw(*m_pPad1);
        m_pMainWindow->draw(*m_pPad2);
        m_pMainWindow->draw(*m_pBall);

        std::stringstream l_DisplayText;
        l_DisplayText << l_pPad1Score << " : " << l_Pad2Score;
        l_Score.setString(l_DisplayText.str());
        m_pMainWindow->draw(l_Score);

        m_pMainWindow->display();
    }

    m_pMainWindow->close();
    FLoaderDestroy();
}
