#include "../include/State.hpp"
#include "../include/Vec2.hpp"
#include "../include/Game.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"
#include "../include/Alien.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/Character.hpp"

#include <iostream>
#include <fstream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_NET
#include "../include/SDL_include.hpp"

#define PI 3.14159265

using namespace std;

State::State()
{
  this->quitRequested = false;

  this->started = false;

  GameObject *initialize = new GameObject();

  Component *bg = new Sprite(*initialize);

  initialize->AddComponent(bg);

  Component *cameraFollower = new CameraFollower(*initialize);

  initialize->AddComponent(cameraFollower);

  Component *music = new Music(*initialize);

  initialize->AddComponent(music);

  this->objectArray.emplace_back(initialize);

  // this->objectArray.emplace_back(tileMapObject);

  GameObject *characterObject = new GameObject();

  Component *character = new Character(*characterObject, "assets/img/MeninaSpriteSheet.png", 3);

  characterObject->AddComponent(character);

  Sprite *characterSprite = (Sprite *)characterObject->GetComponent("Image");

  this->objectArray.emplace_back(characterObject);

  this->LoadAssets();
}

State::~State()
{
  this->objectArray.clear();
}

void State::LoadAssets()
{
  GameObject *initialize = static_cast<GameObject *>(this->objectArray[0].get());

  Sprite *bg = static_cast<Sprite *>(initialize->GetComponent("Image"));

  bg->Open("./assets/img/sala_horizontal.png");


  bg->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  initialize->box.x = 0;
  initialize->box.y = 0;

  bg->Render();

  Music *music = static_cast<Music *>(initialize->GetComponent("Sound"));

  music->Open("./assets/audio/music_mistery.mp3");

  music->Play(-1);
}

void State::Update(float dt)
{

  Camera::Update(dt);

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
  {
    this->quitRequested = true;
  }

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    this->objectArray[i]->Update(dt);
  }

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    if (this->objectArray[i]->IsDead())
    {
      this->RemoveObject(i);
      i--;
    }
  }
}

void State::Render()
{
  for (int i = 0; i < (int)this->objectArray.size(); i++)
    this->objectArray[i]->Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{

  shared_ptr<GameObject> shared_go(go);

  this->objectArray.push_back(shared_go);

  if (this->started)
    shared_go->Start();

  weak_ptr<GameObject> weak_go(shared_go);

  return weak_go;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{

  for (int i = 0; i < (int)this->objectArray.size(); i++)
  {
    if (this->objectArray[i].get() == go)
    {
      weak_ptr<GameObject> weak_go(this->objectArray[i]);
      return weak_go;
    }
  }

  return {};
}

void State::RemoveObject(int position)
{
  this->objectArray.erase(this->objectArray.begin() + position);
}

void State::Start()
{

  this->LoadAssets();

  for (int i = 0; i < (int)this->objectArray.size(); i++)
    this->objectArray[i]->Start();

  this->started = true;
}