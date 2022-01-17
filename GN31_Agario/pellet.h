#pragma once

#include <NearLib/game-object.h>

class Pellet : public Near::GameObject{
public:
  void init(Near::Layer* layer) override;
  void draw() override;
private:
  Near::Math::Color color;
  std::shared_ptr<Near::Texture> texture;
};
