#include "../include/ChapterOne.hpp"
#include "../include/Character.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Mouse.hpp"
#include "../include/Object.hpp"

using namespace std;

ChapterOne::ChapterOne() 
: inventory(new GameObject()), inventory_icon(new GameObject()), bianca(new GameObject()), tv(new GameObject()), phone(new GameObject()),
background(new GameObject()), mouse(new GameObject())
{
  Sprite *background_sprite = new Sprite(*background);

  background->AddComponent(background_sprite);


  Character *bianca_character = new Character(*bianca, "assets/img/spritesheet.png", 7);

  bianca->AddComponent(bianca_character);

  
  Sprite *inventory_sprite = new Sprite(*inventory_icon, "assets/img/bookIcon.png");

  inventory_icon->AddComponent(inventory_sprite);

 
 
  Object *phone_obj = new Object(*phone, "assets/img/telefoneOutline.png");

  phone->AddComponent(phone_obj);


  Mouse *mouse_cpt = new Mouse(*mouse, "assets/img/cursor.png");

  mouse->AddComponent(mouse_cpt);



  AddObject(background);

  AddObject(bianca);

  AddObject(inventory_icon);

  AddObject(inventory);

  AddObject(tv);

  AddObject(phone);

  AddObject(mouse);
}

ChapterOne::~ChapterOne(){}


void ChapterOne::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());

  GameObject *inventory_go = static_cast<GameObject *>(objectArray[2].get());

  Sprite *background = static_cast<Sprite *>(go->GetComponent("Image"));

  background->Open("assets/img/salafinal.png");

  background->SetClip(0, 0, Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

  go->box.x = 0;
  go->box.y = 0;

  inventory_go->box.x = 30 * Game::GetInstance().GetScreenScale().x;
  inventory_go->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  inventory->box.x = 300 * Game::GetInstance().GetScreenScale().x;
  inventory->box.y = 30 * Game::GetInstance().GetScreenScale().y;

  Sprite *phone_sprite = static_cast<Sprite*>(phone->GetComponent("Image"));

  phone_sprite->SetScale(5.0, 5.0);

  phone->box.x = 1300 * Game::GetInstance().GetScreenScale().x;
  phone->box.y = 500 * Game::GetInstance().GetScreenScale().y;

  background->Render();
}

void ChapterOne::Update(float dt) {

  InputManager &input = InputManager::GetInstance();

  Component *inventory_cpt = inventory->GetComponent("Image");

  input.Update();

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }
  else if (input.KeyPress(TAB_KEY) && inventory_cpt == nullptr)
  {
    Sprite *inventory_menu_sprite = new Sprite(*inventory, "assets/img/inventory.png");
    inventory->AddComponent(inventory_menu_sprite);
  }
  else if (input.KeyPress(TAB_KEY) &&  inventory_cpt != nullptr)
  {
    inventory->RemoveComponent(inventory_cpt);
  }

  UpdateArray(dt);
}

void ChapterOne::Render() {
  RenderArray();
}

void ChapterOne::Start() {
  LoadAssets();

  StartArray();

  started = true;
}

void ChapterOne::Pause() {}

void ChapterOne::Resume(){
  Camera::Unfollow();
}