#pragma once

#include <NearLib/scene.h>
#include <NearLib/fps-counter.h>
#include <NearLib/shader.h>

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
};
