#pragma once

#include <NearLib/scene.h>
#include <NearLib/fps-counter.h>
#include <NearLib/shader.h>

#include "game-connection.h"
#include "player.h"
#include "player-camera.h"
#include "pellet.h"

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
  std::shared_ptr<PlayerCamera> camera;
  GameConnection connection;
  unsigned int playerId;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
  std::unordered_map<unsigned int, std::shared_ptr<Pellet>> pellets;
  std::shared_ptr<Player> getMe();
  std::shared_ptr<Player> getPlayer(unsigned int playerId);
  void disconnect();
};
