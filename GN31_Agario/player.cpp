#include "pch.h"
#include "player.h"

void Player::init(Near::Layer* layer){
  super::init(layer);
  texture = Near::Assets::textures()->getOrLoad("assets/textures/player.png");
}

void Player::update(float deltaTime){
  super::update(deltaTime);
}

void Player::draw(){
  auto* r = Near::renderer2D();
  r->setTexture(texture.get());
  r->fillRect(Near::Math::Vector2(transform.position.x, transform.position.y), Near::Math::Vector2(200, 200));
}

void Player::uninit(){
  texture.reset();
  super::uninit();
}

void Player::setName(const char* name){
  strcpy_s(this->name, sizeof(this->name), name);
}
