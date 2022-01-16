#include "pch.h"
#include "player.h"

void Player::init(Near::Layer* layer){
  super::init(layer);
  texture = Near::Assets::textures()->getOrLoad("assets/textures/player.png");
  font = Near::Assets::fonts()->get("Inter");
}

void Player::update(float deltaTime){
  super::update(deltaTime);
  if(controllable){
    int mouseX = Near::input()->getMouseX();
    int mouseY = Near::input()->getMouseY();
    int dirX = mouseX - Near::renderer()->getWidth() / 2;
    int dirY = mouseY - Near::renderer()->getHeight() / 2;
    float direction = std::atan2(static_cast<float>(dirX), static_cast<float>(dirY));
    directionChanged = direction != this->direction;
    this->direction = direction;
  }
}

void Player::draw(){
  auto* r = Near::renderer2D();
  r->setTexture(texture.get());
  Near::Math::Vector2 pos(transform.position.x, transform.position.y);
  r->fillRect(pos, Near::Math::Vector2(static_cast<float>(size)), Near::Math::Vector2(0.5f, 0.5f));
  font->drawText(name, pos, Near::Math::Vector2(0.5f, 0.5f), 16, Near::Math::Color(0, 0, 0, 1));
}

void Player::uninit(){
  texture.reset();
  super::uninit();
}

void Player::setName(const char* name){
  strcpy_s(this->name, sizeof(this->name), name);
}

void Player::setSize(int size){
  this->size = size;
}

void Player::setControllable(bool controllable){
  this->controllable = controllable;
}

float Player::getDirection(){
  return direction;
}

bool Player::hasDirectionChanged(){
  return directionChanged;
}
