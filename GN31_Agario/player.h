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
  void setSize(int size);
  void setControllable(bool controllable);
  float getDirection();
  bool hasDirectionChanged();
private:
  char name[MAX_NAME_LENGTH];
  int size;
  bool controllable;
  float direction;
  bool directionChanged;
  std::shared_ptr<Near::Texture> texture;
  std::shared_ptr<Near::Font::Font> font;
};
