#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/InputManager.hpp"

using namespace std;

extern const float DEG45;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){
  Sprite *penguin_body_sprite = new Sprite(associated, "assets/img/penguin.png");

  this->associated.AddComponent(penguin_body_sprite);

  this->angle = 0.0F;

  Vec2 speed{1, 0};

  this->speed = speed;

  this->linearSpeed = 0.0F;

  this->hp = 30;

  this->player = this;
};

void PenguinBody::Start(){
  State &state = Game::GetInstance().GetState();

  GameObject *penguin_cannon_object = new GameObject();

  weak_ptr<GameObject> penguin_body = state.GetObjectPtr(&this->associated);

  PenguinCannon *penguin_cannon = new PenguinCannon(*penguin_cannon_object, penguin_body);

  penguin_cannon_object->AddComponent(penguin_cannon);

  this->pcannon = state.AddObject(penguin_cannon_object);
};

PenguinBody::~PenguinBody(){
  this->player = nullptr;
};

void PenguinBody::Update(float dt){
  InputManager &input = InputManager::GetInstance();

  float acceleration = .5F;

  float speed_rotation = DEG45 * dt;

  bool w_pressed = input.isKeyDown(W_KEY), s_pressed = input.isKeyDown(S_KEY);
  bool a_pressed = input.isKeyDown(A_KEY), d_pressed = input.isKeyDown(D_KEY);

  if(w_pressed) {
    if (this->linearSpeed <= 10.0F)
    {
      this->linearSpeed += acceleration * dt;
    }
  }
  
  if (s_pressed) {
    if(this->linearSpeed >= - 10.0F){
      this->linearSpeed -= acceleration * dt;
    }
  }
  
  if (a_pressed) {
    this->angle += speed_rotation;
  }

  if (d_pressed) {
    this->angle -= speed_rotation;
  }

  if (this->linearSpeed <= .001 && this->linearSpeed >= .0)
    this->linearSpeed = 0;

  this->associated.angleDeg = radians_to_degrees(this->angle);

  this->speed = Vec2{100, 0};

  this->speed.rotate(this->angle);

  this->associated.box.x += this->speed.x * this->linearSpeed * dt;
  this->associated.box.y += this->speed.y * this->linearSpeed * dt;


  if (hp <= 0){
    this->associated.RequestDelete();
    GameObject* penguin_cannon = this->pcannon.lock().get();
    penguin_cannon->RequestDelete();
  }
};

void PenguinBody::Render(){};

bool PenguinBody::Is(string type)
{
  if (type == "PenguinBody")
    return true;
  return false;
}