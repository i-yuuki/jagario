#include "pch.h"
#include "game-scene.h"

#include "background.h"

void GameScene::init(){
  Scene::init();
  getLayer(LAYER_OBJECTS)->createGameObject<Background>(5000, 128);
}

void GameScene::draw(){
  auto* r = Near::renderer2D();
  r->begin();
  Scene::draw();
  r->end();
}
