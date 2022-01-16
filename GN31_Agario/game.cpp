#include "pch.h"
#include "game.h"

#include "game-scene.h"
#include "player.h"

void Game::init(){
  connection.init();
  scene = std::make_unique<GameScene>();
  scene->init();
  // Renderer2D氏頂点シェーダー自動でついてくるけど
  // 頂点シェーダーつけてなかったから手動で
  vertexShader = Near::Assets::vertexShaders()->getOrLoad("assets/nearlib/shaders/vs.hlsl");
  Near::renderer()->setVertexShader(vertexShader.get());
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
      }
      case PacketType::S_ADD_PLAYER:
      {
        auto& packet = connection.getPacket<PacketServerAddPlayer>();
        auto playerObj = scene->getLayer(Near::Scene::LAYER_OBJECTS)->createGameObject<Player>();
        playerObj->transform.position = Near::Math::Vector3(packet.posX, packet.posY, 0);
        playerObj->setName(packet.name);
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
