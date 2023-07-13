#include "../include/audio.h"

Audio::Audio()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL Mixer error: %s\n", Mix_GetError());
        exit(1);
    }
}

void Audio::load(std::string audioPath)
{
    this->audioFile = Mix_LoadMUS(audioPath.c_str());

    if (!this->audioFile)
    {
        printf("Audio load error: %s\n", Mix_GetError());
        return exit(1);
    }
}

void Audio::play()
{
    if (Mix_PlayMusic(this->audioFile, 1) == -1)
    {
        printf("Audio error: %s\n", Mix_GetError());
        return exit(1);
    }
}

void Audio::clear()
{
    Mix_FreeMusic(this->audioFile);
    Mix_CloseAudio();
    SDL_Quit();
}