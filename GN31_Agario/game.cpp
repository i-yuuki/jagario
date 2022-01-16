#include "pch.h"
#include "game.h"

#include "game-scene.h"

void Game::init(){
  connection.init();
  scene = std::make_unique<GameScene>();
  scene->init();
  // Renderer2D氏頂点シェーダー自動でついてくるけど
  // 頂点シェーダーつけてなかったから手動で
  vertexShader = Near::Assets::vertexShaders()->getOrLoad("assets/nearlib/shaders/vs.hlsl");
  Near::renderer()->setVertexShader(vertexShader.get());
  Near::Assets::fonts()->add("Inter", "assets/fonts/inter.fnt");
}

void Game::update(){
  fpsCounter.frame();
  float deltaTime = static_cast<float>(fpsCounter.getLastFrameTime());
  scene->beforeUpdate(deltaTime);
  scene->update(deltaTime);
  scene->afterUpdate(deltaTime);
  if(Near::input()->isKeyPressedThisFrame('C')){
    connection.connect("127.0.0.1", u8"てすと");
  }
  while(connection.receivePacket()){
    switch(connection.getPacketType()){
      case PacketType::S_JOIN:
      {
        auto& packet = connection.getPacket<PacketServerJoin>();
        playerId = packet.playerId;
        break;
      }
      case PacketType::S_ADD_PLAYER:
      {
        auto& packet = connection.getPacket<PacketServerAddPlayer>();
        auto playerObj = scene->getLayer(Near::Scene::LAYER_OBJECTS)->createGameObject<Player>();
        players.insert({packet.playerId, playerObj});
        playerObj->transform.position = Near::Math::Vector3(packet.posX, packet.posY, 0);
        playerObj->setName(packet.name);
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
  scene->uninit();
  scene.reset();
  disconnect();
  connection.uninit();
}

void Game::disconnect(){
  if(connection.isConnected()){
    PacketClientLeave packet;
    packet.playerId = playerId;
    connection.sendPacket(packet);
  }
  connection.disconnect();
}
