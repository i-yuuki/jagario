#pragma once

#include <NearLib/game-object.h>

class Game;

class TitleScreen : public Near::GameObject{
public:
  TitleScreen(Game* game);
  void init(Near::Layer* layer) override;
  void update(float deltaTime) override;
  void draw() override;
  void show();
private:
  Game* game;
  bool visible;
  float time;
  std::shared_ptr<Near::Font::Font> font;
  void hide();
};
