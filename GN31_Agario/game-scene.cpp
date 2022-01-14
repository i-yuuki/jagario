#include "pch.h"
#include "game-scene.h"

#include "player.h"

void GameScene::init(){
  Scene::init();
  // Add objects here
  getLayer(LAYER_OBJECTS)->createGameObject<Player>();
}

void GameScene::draw(){
  auto* r = Near::renderer2D();
  r->begin();
  Scene::draw();
  r->end();
}