#include "../lib/State.hpp"
#include <iostream>
#include <fstream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../lib/SDL_include.h"

State::State()
{
  this->quitRequested = false; 
  this->bg = *new Sprite();
  this->music = *new Music();

  this->LoadAssets(); 
}

void State::LoadAssets()
{
  this->bg.Open("./src/assets/sprites/sky.png");
  this->music.Open("./src/assets/music/hells.ogg");
  this->music.Play();
}

void State::Update(float dt)
{
  if (SDL_QuitRequested())
  {
    this->quitRequested = true;
  }
}

void State::Render()
{
  this->bg.Render(0, 0);
  
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

