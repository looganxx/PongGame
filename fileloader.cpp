#include "fileloader.h"

FileLoader* FileLoader::m_pLoaderInstance = nullptr;

FileLoader* FileLoader::getInstance()
{
    if(m_pLoaderInstance == nullptr)
    {
        m_pLoaderInstance = new FileLoader();
    }

    return m_pLoaderInstance;
}

FileLoader::~FileLoader( )
{
    delete m_pTexPad;
    delete m_pTexBall;
    delete m_pTexBackground;
    delete m_pFont;
    delete m_pSoundBuffer;
}

FileLoader::FileLoader()
{
    m_pTexPad = new sf::Texture();
    m_pTexBall = new sf::Texture();
    m_pTexBackground = new sf::Texture();
    m_pFont = new sf::Font();;
    m_pSoundBuffer = new sf::SoundBuffer();;
}

void FileLoader::Destroy(void)
{
    delete m_pLoaderInstance;
}


bool FileLoader::LoadAllFile(void)
{
    if(m_pTexPad->loadFromFile("Data/pad.png") == false)
    {
        return false;
    }
    if(m_pTexBall->loadFromFile("Data/ball.png") == false)
    {
        return false;
    }
    if(m_pTexBackground->loadFromFile("Data/background.png") == false)
    {
        return false;
    }
    if(m_pFont->loadFromFile("Data/arial.ttf") == false)
    {
        return false;
    }
    if(m_pSoundBuffer->loadFromFile("Data/hit.wav") == false)
    {
        return false;
    }

    return true;
}

sf::Texture* FileLoader::getPadTexture(void)
{
    return m_pTexPad;
}

sf::Texture* FileLoader::getBallTexture(void)
{
    return m_pTexBall;
}

sf::Texture* FileLoader::getBackgroundTexture(void)
{
    return m_pTexBackground;
}

sf::Font* FileLoader::getFont(void)
{
    return m_pFont;
}

sf::SoundBuffer* FileLoader::getHitSoundsBuffer(void)
{
    return m_pSoundBuffer;
}
