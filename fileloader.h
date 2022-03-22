#pragma once

#ifndef FILELOADER_H
#define FILELOADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define FLoader() (FileLoader::getInstance())
#define FLoaderDestroy() (FileLoader::Destroy())

class FileLoader
{
public:
    // Get instance
    static FileLoader* getInstance(void);

    // Destroyer
    ~FileLoader();

    // Force Destroy of the singleton instance
    static void Destroy(void);

    // Load all necessary file to the app
    bool LoadAllFile(void);

    // Getters
    sf::Texture* getPadTexture(void);
    sf::Texture* getBallTexture(void);
    sf::Texture* getBackgroundTexture(void);
    sf::Font* getFont(void);
    sf::SoundBuffer* getHitSoundsBuffer(void);

private:

    // Private constructor
    FileLoader();

    // Private instance
    static FileLoader* m_pLoaderInstance;

    // Images
    sf::Texture* m_pTexPad;
    sf::Texture* m_pTexBall;
    sf::Texture* m_pTexBackground;

    // Font
    sf::Font* m_pFont;

    // Sounds
    sf::SoundBuffer* m_pSoundBuffer;
};

#endif // FILELOADER_H
