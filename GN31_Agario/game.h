#pragma once

#include <NearLib/scene.h>
#include <NearLib/fps-counter.h>
#include <NearLib/shader.h>

#include "config.h"
#include "game-connection.h"
#include "player.h"
#include "player-camera.h"
#include "pellet.h"
#include "title-screen.h"

class Game{
public:
  Game();
  void init();
  void update();
  void draw();
  void uninit();
  Config& getConfig();
  void connect();
private:
  Config config;
  std::unique_ptr<Near::Scene> scene;
  Near::FPSCounter fpsCounter;
  std::shared_ptr<Near::VertexShader> vertexShader;
  std::shared_ptr<PlayerCamera> camera;
  std::shared_ptr<TitleScreen> titleScreen;
  GameConnection connection;
  unsigned int playerId;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
  std::unordered_map<unsigned int, std::shared_ptr<Pellet>> pellets;
  std::shared_ptr<Player> getMe();
  std::shared_ptr<Player> getPlayer(unsigned int playerId);
  void disconnect();
};
