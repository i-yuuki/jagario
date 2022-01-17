#include "pch.h"
#include "game.h"

#include "game-scene.h"

Game::Game() : config("config.txt"){
}

void Game::init(){
  config.load();
  connection.init();
  scene = std::make_unique<GameScene>();
  scene->init();
  camera = scene->getLayer(Near::Scene::LAYER_MANAGERS)->createGameObject<PlayerCamera>();
  // Renderer2D氏頂点シェーダー自動でついてくるけど
  // 頂点シェーダーつけてなかったから手動で
  vertexShader = Near::Assets::vertexShaders()->getOrLoad("assets/nearlib/shaders/vs.hlsl");
  Near::renderer()->setVertexShader(vertexShader.get());
  Near::Assets::fonts()->add("Inter", "assets/fonts/inter.fnt");

  titleScreen = scene->getLayer(Near::Scene::LAYER_OVERLAY)->createGameObject<TitleScreen>(this);
  titleScreen->show();
}

void Game::update(){
  fpsCounter.frame();
  float deltaTime = static_cast<float>(fpsCounter.getLastFrameTime());
  scene->beforeUpdate(deltaTime);
  scene->update(deltaTime);
  scene->afterUpdate(deltaTime);
  while(connection.receivePacket()){
    switch(connection.getPacketType()){
      case PacketType::S_JOIN:
      {
        auto& packet = connection.getPacket<PacketServerJoin>();
        playerId = packet.playerId;
        if(auto me = getMe()){
          me->setControllable(true);
          camera->setFollow(me);
        }
        break;
      }
      case PacketType::S_ADD_PLAYER:
      {
        auto& packet = connection.getPacket<PacketServerAddPlayer>();
        auto playerObj = scene->getLayer(Near::Scene::LAYER_OBJECTS)->createGameObject<Player>();
        players.insert({packet.playerId, playerObj});
        playerObj->transform.position = Near::Math::Vector3(packet.posX, packet.posY, 0);
        playerObj->setName(packet.name);
        playerObj->setSize(packet.size);
        break;
      }
      case PacketType::S_REMOVE_PLAYER:
      {
        auto& packet = connection.getPacket<PacketServerRemovePlayer>();
        auto it = players.find(packet.playerId);
        if(it != players.end()){
          it->second->markRemove();
          players.erase(it);
        }
        break;
      }
      case PacketType::S_UPDATE_PLAYER:
      {
        auto& packet = connection.getPacket<PacketServerUpdatePlayer>();
        if(auto player = getPlayer(packet.playerId)){
          player->setPosition(packet.posX, packet.posY);
          player->setSize(packet.size);
        }
        break;
      }
      case PacketType::S_ADD_PELLET:
      {
        auto& packet = connection.getPacket<PacketServerAddPellet>();
        // TODO プレイヤーの1個下のレイヤーに？
        auto pellet = scene->getLayer(Near::Scene::LAYER_OBJECTS)->createGameObject<Pellet>();
        pellet->transform.position.x = packet.posX;
        pellet->transform.position.y = packet.posY;
        pellets.insert({packet.pelletId, pellet});
        break;
      }
      case PacketType::S_REMOVE_PELLET:
      {
        auto& packet = connection.getPacket<PacketServerRemovePellet>();
        auto it = pellets.find(packet.pelletId);
        if(it != pellets.end()){
          it->second->markRemove();
          pellets.erase(it);
        }
        break;
      }
    }
  }
  if(auto me = getMe()){
    if(me->hasDirectionChanged()){
      PacketClientDirection packet;
      packet.playerId = playerId;
      packet.direction = me->getDirection();
      connection.sendPacket(packet);
    }
  }
}

void Game::draw(){
  auto* r = Near::renderer();
  r->clear(Near::Math::Color(1, 1, 1, 1));
  scene->draw();
  r->present();
}

void Game::uninit(){
  vertexShader.reset();
  players.clear();
  titleScreen.reset();
  camera.reset();
  scene->uninit();
  scene.reset();
  disconnect();
  connection.uninit();
}

std::shared_ptr<Player> Game::getMe(){
  return getPlayer(playerId);
}

std::shared_ptr<Player> Game::getPlayer(unsigned int playerId){
  auto it = players.find(playerId);
  return it == players.end() ? nullptr : it->second;
}

Config& Game::getConfig(){
  return config;
}

void Game::connect(){
  for(auto it = players.begin();it != players.end();it ++){
    it->second->markRemove();
  }
  players.clear();

  for(auto it = pellets.begin();it != pellets.end();it ++){
    it->second->markRemove();
  }
  pellets.clear();

  connection.connect(config.address, config.playerName);
}

void Game::disconnect(){
  if(connection.isConnected()){
    PacketClientLeave packet;
    packet.playerId = playerId;
    connection.sendPacket(packet);
  }
  connection.disconnect();
}
