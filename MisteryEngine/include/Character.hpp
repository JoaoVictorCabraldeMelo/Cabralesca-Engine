#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Component.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"

#include <queue>

class Character : public Component  {

  public:
    Character(GameObject &associated, std::string sprite, int frame_count);

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    bool Is(const std::string& type) override;

    enum class Direction
    {
      LEFT,
      RIGHT
    };

    Direction sprite_direction;

  private:
    std::queue<Vec2> destinations;

    Vec2 speed;
};

#endif