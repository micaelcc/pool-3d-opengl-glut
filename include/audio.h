#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "iostream"
class Audio
{
private:
    Mix_Music *audioFile;

public:
    Audio();
    void load(std::string audioPath);
    void play();
    void clear();
};