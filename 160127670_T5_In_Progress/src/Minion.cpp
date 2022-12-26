#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Vec2.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"
#include "../include/State.hpp"

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;


Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated), alienCenter(*alienCenter.lock().get())
{

    Sprite *minion_sprite = new Sprite(associated, "assets/img/minion.png");

    this->associated.AddComponent(minion_sprite);

    this->arc = arcOffsetDeg;

    this->associated.box.w = minion_sprite->GetWidth();

    this->associated.box.h = minion_sprite->GetHeight();
}

void Minion::Start()
{
}

void Minion::Update(float dt)
{
    Vec2 distance_minion_origen{0, 0};

    float ratio = 200;

    if (this->arc == 0)
    {
        distance_minion_origen.x = ratio;
        distance_minion_origen.y = 0;
    }

    float speed = DEG30 * dt;

    this->arc += speed;

    // simple rotation
    distance_minion_origen.x = ratio * cos(this->arc);
    distance_minion_origen.y = ratio * sin(this->arc);

    if (&this->alienCenter != nullptr)
    {
        GameObject &updt_alien_center = this->alienCenter;

        pair<float, float> center = updt_alien_center.box.get_center();

        distance_minion_origen.x += center.first - 10;
        distance_minion_origen.y += center.second + 5;

        this->associated.box.x = distance_minion_origen.x;
        this->associated.box.y = distance_minion_origen.y;
    }
    else
    {
        this->associated.RequestDelete();
        return;
    }
}

void Minion::Render()
{
}

bool Minion::Is(string type)
{
    if (type == "Minion")
        return true;
    return false;
}

void Minion::Shoot(Vec2 target)
{
    Game &instance = Game::GetInstance();

    State &game_state = instance.GetState();

    pair<float, float> center = this->associated.box.get_center();

    Vec2 minion_pos{center.first, center.second};

    float angle_bullet = minion_pos.inclination_two_points(target);

    float distance = minion_pos.distance(target.x, target.y);

    Vec2 result_position;

    result_position.x = minion_pos.x - target.x;
    result_position.y = minion_pos.y - target.y;

    Vec2 base{0, 0};

    float length = result_position.magnitude(base);

    Vec2 normalized_vector{result_position.x / length, result_position.y / length};

    float bullet_speed = normalized_vector.x * BULLET_SPEED;

    GameObject *bullet_go = new GameObject();

    string sprite = "assets/img/minionbullet1.png";

    Component *bullet = new Bullet(*bullet_go, angle_bullet, bullet_speed, 10, distance, sprite);

    bullet_go->AddComponent(bullet);

    game_state.AddObject(bullet_go);
}