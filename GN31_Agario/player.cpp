#include "pch.h"
#include "player.h"

void Player::init(Near::Layer* layer){
  super::init(layer);
  targetPos = transform.position;
  texture = Near::Assets::textures()->getOrLoad("assets/textures/player.png");
  font = Near::Assets::fonts()->get("Inter");
}

void Player::update(float deltaTime){
  super::update(deltaTime);
  transform.position = Near::Math::Vector3::Lerp(transform.position, targetPos, std::min(1.0f, deltaTime / 100.0f));
  if(controllable){
    int mouseX = Near::input()->getMouseX();
    int mouseY = Near::input()->getMouseY();
    int dirX = mouseX - Near::renderer()->getWidth() / 2;
    int dirY = mouseY - Near::renderer()->getHeight() / 2;
    float direction = std::atan2(static_cast<float>(dirX), static_cast<float>(dirY));
    bool boost = Near::input()->isKeyDown(' ');
    controlChanged = direction != this->direction || boost != this->boost;
    this->direction = direction;
    this->boost = boost;
  }
}

void Player::draw(){
  auto* r = Near::renderer2D();
  r->setTexture(texture.get());
  Near::Math::Vector2 pos(transform.position.x, transform.position.y);
  r->fillRect(pos, Near::Math::Vector2(static_cast<float>(size)), Near::Math::Vector2(0.5f, 0.5f));
  font->drawText(name, pos, Near::Math::Vector2(0.5f, 0.5f), std::min(std::max(10.0f, size / 3.0f), 64.0f), Near::Math::Color(0, 0, 0, 1));
}

void Player::uninit(){
  texture.reset();
  super::uninit();
}

const char* Player::getName(){
  return name;
}

void Player::setName(const char* name){
  strcpy_s(this->name, sizeof(this->name), name);
}

int Player::getSize(){
  return size;
}

void Player::setSize(int size){
  this->size = size;
}

void Player::setPosition(float x, float y){
  targetPos.x = x;
  targetPos.y = y;
}

void Player::setControllable(bool controllable){
  this->controllable = controllable;
}

float Player::getDirection(){
  return direction;
}

bool Player::getBoost(){
  return boost;
}

bool Player::hasControlChanged(){
  return controlChanged;
}
