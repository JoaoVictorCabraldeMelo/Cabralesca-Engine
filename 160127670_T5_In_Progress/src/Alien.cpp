#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Vec2.hpp"
#include "../include/Minion.hpp"
#include "../include/Game.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{

  Component *alien_sprite = new Sprite(associated, "assets/img/alien.png");

  this->associated.AddComponent(alien_sprite);

  this->nMinions = nMinions;
}

Alien::~Alien()
{
  while (!this->minionArray.empty())
    this->minionArray.pop_back();
}

void Alien::Start()
{

  Game instance = Game::GetInstance();

  State game_state = instance.GetState();

  weak_ptr<GameObject> alien_go = game_state.GetObjectPtr(&(this->associated));

  shared_ptr<GameObject> shared_alien_go = alien_go.lock();

  cout << "Objeto retornado: " << shared_alien_go.get() << endl;

  for (int i = 0; i < this->nMinions; i++)
  {
    GameObject *minion_go = new GameObject();

    if (shared_alien_go.get() != nullptr) // found the object
    {

      cout << "Vou criar um novo minion !!" << endl;

      Component *minion = new Minion(*minion_go, alien_go, 0.0F);

      minion_go->AddComponent(minion);

      weak_ptr<GameObject> new_minion_go = game_state.AddObject(minion_go);

      this->minionArray.push_back(new_minion_go);
    }
    else
    {
      ofstream logfile("Errors.log", ofstream::app);
      logfile << "Alien Object is null !!!" << endl;
      logfile << "Please don't attach a Minion to a NULL GameObject !!!" << endl;
      break;
    }
  }
}

Alien::Action::Action(ActionType type, float x, float y)
{
  this->type = type;
  this->pos.x = x;
  this->pos.y = y;
}

void Alien::Update(float dt)
{
  // cout << "Delta :" << dt << endl;

  bool left_click = InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);

  bool right_click = InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON);

  int mouse_x = InputManager::GetInstance().GetMouseX();

  int mouse_y = InputManager::GetInstance().GetMouseY();

  if (left_click || right_click)
  {
    int camera_x = Camera::pos.x;
    int camera_y = Camera::pos.y;

    if (left_click)
    {
      Alien::Action new_action = Alien::Action(Action::SHOOT, mouse_x + camera_x, mouse_y + camera_y);
      this->taskQueue.push(new_action);
    }
    else
    {
      Alien::Action new_action = Alien::Action(Action::MOVE, mouse_x + camera_x, mouse_y + camera_y);
      this->taskQueue.push(new_action);
    }
  }

  if (!this->taskQueue.empty())
  {

    Alien::Action pendent_action = this->taskQueue.front();

    // cout << "Posicao pendente eixo X e eixo Y: " << pendent_action.pos.x << " " << pendent_action.pos.y << endl;

    float alien_x = this->associated.box.x;
    float alien_y = this->associated.box.y;

    this->speed.x = 175;
    this->speed.y = 175;

    Vec2 inital_position{alien_x, alien_y};
    Vec2 final_position{pendent_action.pos.x, pendent_action.pos.y};
    Vec2 result_position;

    result_position.x = final_position.x - inital_position.x;
    result_position.y = final_position.y - inital_position.y;

    Vec2 base{0, 0};

    float length_vector = result_position.magnitude(base);

    Vec2 normalized_vector{result_position.x / length_vector, result_position.y / length_vector};

    float distance = pendent_action.pos.distance(alien_x, alien_y);

    // cout << "Distância: " << distance << endl;
    if (distance <= 10.0)
    {
      this->associated.box.x = pendent_action.pos.x;
      this->associated.box.y = pendent_action.pos.y;
      this->taskQueue.pop();
    }
    else if (pendent_action.type == Action::MOVE)
    {
      this->associated.box.x += normalized_vector.x * this->speed.x * dt;
      this->associated.box.y += normalized_vector.y * this->speed.y * dt;
    }
    else if (pendent_action.type == Action::SHOOT)
    {
      this->taskQueue.pop();
    }
  }

  if (this->hp <= 0)
    this->associated.RequestDelete();
}

void Alien::Render()
{
}

bool Alien::Is(string type)
{
  if (type == "Alien")
    return true;
  return false;
}