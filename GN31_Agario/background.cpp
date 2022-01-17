#include "pch.h"
#include "background.h"

Background::Background(float size, float gridSize) : size(size), gridSize(gridSize){
}

void Background::init(Near::Layer* layer){
  texture = Near::Assets::textures()->getOrLoad("assets/textures/grid.png");
}

void Background::draw(){
  auto* r = Near::renderer2D();
  Near::Math::Vector2 pos(-size / 2);
  Near::Math::Vector2 size(size);
  r->setTexture(texture.get());
  r->fillRectUV(pos, size, pos / gridSize, size / gridSize, Near::Math::Vector2::Zero, Near::Math::Color(0, 0, 0, 0.1f));
}
