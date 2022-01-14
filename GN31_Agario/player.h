#pragma once

#include <NearLib/game-object.h>
#include <NearLib/texture.h>

class Player : public Near::GameObject{
public:
  void init(Near::Layer* layer) override;
  void update(float deltaTime) override;
  void draw() override;
  void uninit() override;
private:
  std::shared_ptr<Near::Texture> texture;
};
