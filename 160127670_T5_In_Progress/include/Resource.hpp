#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <unordered_map>
#include <string>


class Resource
{
private:

static std::unordered_map<std::string, SDL_Texture*> imageTable;
static std::unordered_map<std::string, Mix_Music*> musicTable;
static std::unordered_map<std::string, Mix_Chunk*> soundTable;

public:

  static SDL_Texture* GetImage(std::string file);

  static void ClearImages();

  static Mix_Music* GetMusic(std::string file);

  static void ClearMusic();

  static Mix_Chunk* GetSound(std::string file);

  static void ClearSounds();

};


#endif


