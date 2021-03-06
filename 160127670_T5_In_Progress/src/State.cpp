#include "../include/State.hpp"
#include "../include/Vec2.hpp"
#include "../include/Face.hpp"
#include "../include/Game.hpp"
#include "../include/TileMap.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFollower.hpp"
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

  this->started = true //Inicializando started no constructor

  GameObject *initialize = new GameObject();

  GameObject *tileMapObject = new GameObject();

  TileSet *tileSet = new TileSet(64, 64, "./assets/img/tileset.png");

  Component *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);

  Component *bg = new Sprite(*initialize);

  initialize->AddComponent(bg);

  Component *cameraFollower = new CameraFollower(*initialize);

  initialize->AddComponent(cameraFollower);

  Component *music = new Music(*initialize);

  initialize->AddComponent(music);

  this->objectArray.emplace_back(initialize);

  this->objectArray.emplace_back(tileMapObject);

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

  bg->Open("./assets/img/ocean.jpg");

  bg->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  initialize->box.x = 0;
  initialize->box.y = 0;

  bg->Render();

  Music *music = static_cast<Music *>(initialize->GetComponent("Sound"));

  music->Open("./assets/audio/stageState.ogg");

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

  if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
  {
    Vec2 objPos = Vec2(200, 0).rotate(-PI + PI * (rand() % 1001) / 500.0) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    AddObject((int)objPos.x, (int)objPos.y);
  }

  for (auto it = this->objectArray.begin(); it < this->objectArray.end(); ++it)
  {
    if ((*it)->IsDead())
      this->RemoveObject(it);
    else
      (*it)->Update(dt);
  }
}

void State::Render()
{

  for (auto &object : objectArray)
    object->Render();
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{

  shared_ptr<GameObject> shared_go = make_shared<GameObject>(*go);

  this->objectArray.push_back(shared_go);

  if (this->started)
    shared_go->Start();

  weak_ptr<GameObject> weak_go = shared_go;

  return weak_go;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{

  weak_ptr<GameObject> found_object = nullptr;

  for (auto &object : this->objectArray)
  {
    if (object == *go)
      found_object = object;
  }

  return found_object;
}

void State::RemoveObject(vector<unique_ptr<GameObject>>::iterator it)
{
  this->objectArray.erase(it);
}

void State::Start()
{

  this->LoadAssets();

  for (auto &go : this->objectArray)
  {
    go->Start();
  }
  this->started = true;
}
