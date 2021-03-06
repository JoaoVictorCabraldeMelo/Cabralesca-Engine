#ifndef _ALIEN_H_
#define _ALIEN_H_

#include "Component.hpp"
#include "Vec2.hpp"

#include <queue>

class Alien : public Component
{
public:
  Alien(GameObject &associated, int nMinions);

  ~Alien();

  void Start();

  void Update(float dt);

  void Render();

  bool Is(std::string type);

private:
  class Action
  {
  public:
    enum ActionType
    {
      MOVE,
      SHOOT
    };

    Action(ActionType Action, float x, float y);

    ActionType type;

    static Vec2 pos;
  };

  int hp;

  std::queue<Action> taskAction;

  std::vector<std::weak_ptr<GameObject>> minionArray;

  static Vec2 speed;
};
#endif