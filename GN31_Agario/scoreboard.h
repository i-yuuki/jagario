#pragma once

#include <NearLib/game-object.h>

class Game;

class Scoreboard : public Near::GameObject{
public:
  Scoreboard(Game* game);
  void init(Near::Layer* layer) override;
  void draw() override;
private:
  Game* game;
  std::shared_ptr<Near::Font::Font> font;
};
