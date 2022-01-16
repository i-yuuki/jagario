#include "pch.h"
#include "player.h"

void Player::init(Near::Layer* layer){
  super::init(layer);
  texture = Near::Assets::textures()->getOrLoad("assets/textures/player.png");
  font = Near::Assets::fonts()->get("Inter");
}

void Player::update(float deltaTime){
  super::update(deltaTime);
}

void Player::draw(){
  auto* r = Near::renderer2D();
  r->setTexture(texture.get());
  Near::Math::Vector2 pos(transform.position.x, transform.position.y);
  r->fillRect(pos, Near::Math::Vector2(200, 200), Near::Math::Vector2(0.5f, 0.5f));
  font->drawText(name, pos, Near::Math::Vector2(0.5f, 0.5f), 16, Near::Math::Color(0, 0, 0, 1));
}

void Player::uninit(){
  texture.reset();
  super::uninit();
}

void Player::setName(const char* name){
  strcpy_s(this->name, sizeof(this->name), name);
}
