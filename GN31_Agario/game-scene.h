#pragma once

#include <NearLib/scene.h>

class GameScene : public Near::Scene{
public:
  void init() override;
  void draw() override;
};
