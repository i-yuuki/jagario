#include "pch.h"
#include "game.h"

void Game::init(){
}

void Game::update(){
}

void Game::draw(){
  auto* r = Near::renderer();
  r->clear(Near::Math::Color(1, 1, 1, 1));
  r->present();
}

void Game::uninit(){

}
