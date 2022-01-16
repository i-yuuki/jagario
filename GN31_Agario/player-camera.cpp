#include "pch.h"
#include "player-camera.h"

void PlayerCamera::update(float deltaTime){
  Near::Math::Vector3 targetPos;
  if(auto p = player.lock()){
    targetPos = -p->transform.position;
    targetPos.x += Near::renderer()->getWidth() / 2.0f;
    targetPos.y += Near::renderer()->getHeight() / 2.0f;
  }
  float t = std::min(1.0f, deltaTime / 500.0f);
  transform.position = Near::Math::Vector3::Lerp(transform.position, targetPos, t);
  // TODO 大きさに応じた拡大など
}

void PlayerCamera::draw(){
  Near::renderer2D()->setTransform(transform.createTransform());
}

void PlayerCamera::setFollow(std::weak_ptr<Player> player){
  this->player = player;
}

