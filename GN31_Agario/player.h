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
  const char* getName();
  void setName(const char* name);
  int getSize();
  void setSize(int size);
  void setPosition(float x, float y);
  void setControllable(bool controllable);
  float getDirection();
  bool hasControlChanged();
  bool getBoost();
private:
  char name[MAX_NAME_LENGTH];
  int size;
  Near::Math::Vector3 targetPos;
  bool controllable;
  float direction;
  bool boost;
  bool controlChanged;
  std::shared_ptr<Near::Texture> texture;
  std::shared_ptr<Near::Font::Font> font;
};
