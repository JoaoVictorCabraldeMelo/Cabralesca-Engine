#include "../include/PenguinCannon.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Bullet.hpp"

using namespace std;

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody)
  : Component(associated)
{
  Sprite *penguin_cannon_sprite = new Sprite(associated, "assets/img/cubngun.png");

  associated.AddComponent(penguin_cannon_sprite);

  this->pbody = penguinBody;

  this->angle = 0.0F;

  associated.box.w = penguin_cannon_sprite->GetWidth();
  associated.box.h = penguin_cannon_sprite->GetHeight();
};

void PenguinCannon::Update(float dt) {
  GameObject *go = this->pbody.lock().get();

  if (go == NULL) {
    this->associated.RequestDelete();
  }

  Vec2 coord = go->box.get_center();

  this->associated.box.x = coord.x;
  this->associated.box.y = coord.y;

  InputManager &input = InputManager::GetInstance();

  int x_value = input.GetMouseX() + Camera::pos.x, y_value = input.GetMouseY() + Camera::pos.y;

  Vec2 first_point = this->associated.box.get_center();

  Vec2 second_point {(float) x_value, (float) y_value};

  this->angle = first_point.inclination_two_points(second_point);

  this->associated.angleDeg = radians_to_degrees(this->angle);

  this->angle = this->associated.angleDeg;

  bool mouse_left_clicked = input.MousePress(LEFT_MOUSE_BUTTON);

  if (mouse_left_clicked) {
    this->Shoot();
  }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{
  if (type == "PenguinCannon")
    return true;
  return false;
}

void PenguinCannon::Shoot()
{
  State &state = Game::GetInstance().GetState();

  Vec2 center = this->associated.box.get_center();

  GameObject *bullet_go = new GameObject();

  bullet_go->box.x = center.x + this->associated.box.w / 2.0;
  bullet_go->box.y = center.y + this->associated.box.h / 2.0;

  string sprite = "assets/img/penguinbullet.png";

  Component *bullet = new Bullet(*bullet_go, this->angle, 5.0F, 4, 10, 1000.0F, sprite);

  bullet_go->AddComponent(bullet);

  state.AddObject(bullet_go);
}