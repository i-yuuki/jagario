#pragma once

#include <NearLib/game-object.h>

#include "player.h"

class PlayerCamera : public Near::GameObject{
public:
  void update(float deltaTime) override;
  void draw() override;
  void setFollow(std::weak_ptr<Player> player);
private:
  std::weak_ptr<Player> player;
};
