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
  connection.uninit();
}
