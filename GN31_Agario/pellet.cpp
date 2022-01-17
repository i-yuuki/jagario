#include "pch.h"
#include "pellet.h"

#include <random>

void Pellet::init(Near::Layer* layer){
  super::init(layer);

  std::mt19937 rand(std::random_device{}());
  // power play
  transform.rotation = Near::Math::Quaternion::CreateFromAxisAngle(Near::Math::Vector3::Forward, std::uniform_real_distribution<float>(0, 6.18f)(rand));

  std::uniform_real_distribution<float> dist(0.5f, 1);
  color = Near::Math::Color(dist(rand), dist(rand), dist(rand), 1.0f);

  texture = Near::Assets::textures()->getOrLoad("assets/textures/pellet.png");
}

void Pellet::draw(){
  auto* r = Near::renderer2D();
  r->setTexture(texture.get());
  Near::Math::Vector2 pos(transform.position.x, transform.position.y);
  r->fillRect(pos, Near::Math::Vector2(10), Near::Math::Vector2(0.5f), color);
}
