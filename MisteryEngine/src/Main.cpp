#include "../include/Game.hpp"
#include "../include/ChapterOne.hpp"
#include <ctime>
#include <cstdlib>

int main() {

  srand (static_cast <unsigned> (time(0)));

  Game &game = Game::GetInstance();
  
  State *initial_state = new ChapterOne();

  game.Push(initial_state);

  game.Run();

  return 0;
}