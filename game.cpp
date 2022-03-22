#include "game.h"
#include "fileloader.h"
#include <iostream>
#include <sstream>

Game::Game()
{
    // file includes
    if(FLoader()->LoadAllFile() == false)
    {
        return;
    }

    // Window
    m_pMainWindow = new sf::RenderWindow(sf::VideoMode(800,600), "Pong Game");
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
    l_Score.setPosition(m_pMainWindow->getSize().x/2 -30 , 20);

    sf::Sound l_HitSound;
    l_HitSound.setBuffer(*(FLoader()->getHitSoundsBuffer()));

    //////////////// Shapes /////////////////
    // Background
    sf::RectangleShape l_Background;
    l_Background.setSize(sf::Vector2f(800, 600));
    l_Background.setPosition(0, 0);
    l_Background.setTexture(FLoader()->getBackgroundTexture());

    //////////////////////////////////////////

    // States
    bool l_boLeftUp = false, l_boLeftDown = false; // for Pad1
    bool l_boRightUp = false, l_boRightDown = false; // for Pad2
    bool l_isPad1Moving = false, l_isPad2Moving = false;

    // Variable
    int l_yVelocityPad1 = 0, l_yVelocityPad2 = 0;
    int l_xVelocityBall = -3, l_yVelocityBall = -3;
    int m_pPad1Score = 0, l_Pad2Score = 0;

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

        // Pad1
        if(l_boLeftUp == true)
        {
            l_yVelocityPad1 = -5;
            l_isPad1Moving = true;
        }

        if(l_boLeftDown == true)
        {
            l_yVelocityPad1 = 5;
            l_isPad1Moving = true;
        }

        // Do not move the pad
        if(l_boLeftUp == l_boLeftDown)
        {
            l_yVelocityPad1 = 0;
            l_isPad1Moving = false;
        }

        m_pPad1->move(0, l_yVelocityPad1);

        // check pad out of bounds
        if(m_pPad1->IsPadOutOfBound(m_pMainWindow) == true)
        {
            l_isPad1Moving = false;
            m_pPad1->move(0, -l_yVelocityPad1);
        }

        // Pad2
        if(l_boRightUp == true)
        {
            l_isPad2Moving = true;
            l_yVelocityPad2 = -5;
        }

        if(l_boRightDown == true)
        {
            l_isPad2Moving = true;
            l_yVelocityPad2 = 5;
        }

        // Do not move the pad
        if(l_boRightUp == l_boRightDown)
        {
            l_isPad2Moving = false;
            l_yVelocityPad2 = 0;
        }

        m_pPad2->move(0, l_yVelocityPad2);

        // check pad out of bounds
        if(m_pPad2->IsPadOutOfBound(m_pMainWindow) == true)
        {
            l_isPad2Moving = false;
            m_pPad2->move(0, -l_yVelocityPad2);
        }


        // Ball
        m_pBall->move(l_xVelocityBall, l_yVelocityBall);

        // check ball out of bounds
        if(m_pBall->IsBallOutOfBound() == true)
        {
            l_yVelocityBall = -l_yVelocityBall;
            m_pBall->move(l_xVelocityBall, l_yVelocityBall);
        }

        // Score for pad 2
        if(m_pBall->IsBallOutLeft() == true)
        {
            l_Pad2Score++;
            m_pBall->setPosition(400, 300);
        }

        // Score for pad 1
        if(m_pBall->IsBallOutRight() == true)
        {
            m_pPad1Score++;
            m_pBall->setPosition(400, 300);
        }

        if(m_pBall->getGlobalBounds().intersects(m_pPad1->getGlobalBounds()) == true)
        {
            l_HitSound.play();

            if(l_yVelocityPad1 < 0 && l_isPad1Moving)
            {
                l_yVelocityBall = -l_yVelocityBall;
            }

            l_xVelocityBall = -l_xVelocityBall;

            m_pBall->move(l_xVelocityBall, l_yVelocityBall);
        }


        if(m_pBall->getGlobalBounds().intersects(m_pPad2->getGlobalBounds()) == true)
        {
            l_HitSound.play();

            if(l_yVelocityPad2 < 0 && l_isPad2Moving)
            {
                l_yVelocityBall = -l_yVelocityBall;
            }

            l_xVelocityBall = -l_xVelocityBall;

            m_pBall->move(l_xVelocityBall, l_yVelocityBall);
        }

        // RENDERING
        m_pMainWindow->clear();

        m_pMainWindow->draw(l_Background);
        m_pMainWindow->draw(*m_pPad1);
        m_pMainWindow->draw(*m_pPad2);
        m_pMainWindow->draw(*m_pBall);

        std::stringstream l_DisplayText;
        l_DisplayText << m_pPad1Score << " : " << l_Pad2Score;
        l_Score.setString(l_DisplayText.str());
        m_pMainWindow->draw(l_Score);

        m_pMainWindow->display();
    }

    m_pMainWindow->close();
    FLoaderDestroy();
}
