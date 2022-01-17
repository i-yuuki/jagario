#include "pch.h"
#include "player-camera.h"

void PlayerCamera::update(float deltaTime){
  Near::Math::Vector3 targetPos = transform.position;
  Near::Math::Vector3 targetScale = transform.scale;
  if(auto p = player.lock()){
    targetPos = p->transform.position;
    targetScale = Near::Math::Vector3(1 + std::max((100 - p->getSize()) / 50.0f, 0.0f));
  }
  float t = std::min(1.0f, deltaTime / 200.0f);
  transform.position = Near::Math::Vector3::Lerp(transform.position, targetPos, t);
  transform.scale = Near::Math::Vector3::Lerp(transform.scale, targetScale, t);
}

void PlayerCamera::draw(){
  Near::Math::Vector3 screenCenter(Near::renderer()->getWidth() / 2.0f, Near::renderer()->getHeight() / 2.0f, 0);
  Near::renderer2D()->setTransform(Near::Math::Matrix::CreateTranslation(-transform.position) * Near::Math::Matrix::CreateScale(transform.scale) * Near::Math::Matrix::CreateTranslation(screenCenter));
}

void PlayerCamera::setFollow(std::weak_ptr<Player> player){
  this->player = player;
  if(auto p = player.lock()){
    transform.position = p->transform.position;
  }
}

