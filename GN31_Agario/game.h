#pragma once

#include <NearLib/scene.h>
#include <NearLib/fps-counter.h>
#include <NearLib/shader.h>

#include "game-connection.h"

class Game{
public:
  void init();
  void update();
  void draw();
  void uninit();
private:
  std::unique_ptr<Near::Scene> scene;
  Near::FPSCounter fpsCounter;
  std::shared_ptr<Near::VertexShader> vertexShader;
  GameConnection connection;
  unsigned int playerId;
  void disconnect();
};
