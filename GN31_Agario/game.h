#pragma once

#include <NearLib/scene.h>
#include <NearLib/fps-counter.h>

class Game{
public:
  void init();
  void update();
  void draw();
  void uninit();
private:
  std::unique_ptr<Near::Scene> scene;
  Near::FPSCounter fpsCounter;
};
