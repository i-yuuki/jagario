#pragma once

#include <NearLib/game-object.h>

class Background : public Near::GameObject{
public:
  Background(float size, float gridSize);
  void init(Near::Layer* layer) override;
  void draw() override;
private:
  float size;
  float gridSize;
  std::shared_ptr<Near::Texture> texture;
};
