#pragma once

#include <NearLib/game-object.h>
#include <NearLib/texture.h>

#include "packet.h"

class Player : public Near::GameObject{
public:
  void init(Near::Layer* layer) override;
  void update(float deltaTime) override;
  void draw() override;
  void uninit() override;
  void setName(const char* name);
private:
  char name[MAX_NAME_LENGTH];
  std::shared_ptr<Near::Texture> texture;
};
