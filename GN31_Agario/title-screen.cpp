#include "pch.h"
#include "title-screen.h"

#include "game.h"

TitleScreen::TitleScreen(Game* game) : GameObject(), game(game){
}

void TitleScreen::init(Near::Layer* layer){
  super::init(layer);

  font = Near::Assets::fonts()->get("Inter");
}

void TitleScreen::update(float deltaTime){
  if(!visible) return;
  time += deltaTime;
  if(Near::input()->isKeyPressedThisFrame(VK_RETURN)){
    hide();
    game->connect("127.0.0.1", u8"てすと");
  }
}

void TitleScreen::draw(){
  if(!visible) return;
  float alpha = std::min(time / 1000, 1.0f);
  Near::Math::Color black(0, 0, 0, alpha);
  Near::Math::Color gray(0.5f, 0.5f, 0.5f, alpha);
  Near::Math::Vector2 screenSize(Near::renderer()->getWidth(), Near::renderer()->getHeight());
  Near::Math::Vector2 screenCenter = screenSize / 2;
  auto* r = Near::renderer2D();
  r->setTransform(Near::Math::Matrix::Identity);
  r->setTexture(nullptr);
  r->fillRect(Near::Math::Vector2::Zero, screenSize, Near::Math::Vector2::Zero, Near::Math::Color(1, 1, 1, alpha / 2));
  font->drawText(u8"Jagario",       screenCenter + Near::Math::Vector2(  0, -128), Near::Math::Vector2(0.5f),    64, Near::Math::Color(1.000f, 0.341f, 0.133f, alpha));
  font->drawText(u8"プレイヤー名:", screenCenter + Near::Math::Vector2( -8,  -24), Near::Math::Vector2(1, 0.5f), 16, gray);
  font->drawText(u8"てすと",        screenCenter + Near::Math::Vector2(  8,  -24), Near::Math::Vector2(0, 0.5f), 16, black);
  font->drawText(u8"接続先:",       screenCenter + Near::Math::Vector2( -8,    0), Near::Math::Vector2(1, 0.5f), 16, gray);
  font->drawText(u8"127.0.0.1",     screenCenter + Near::Math::Vector2(  8,    0), Near::Math::Vector2(0, 0.5f), 16, black);
  font->drawText(u8"[C] で設定編集 [R] で設定読み込み", screenCenter + Near::Math::Vector2(  0,   24), Near::Math::Vector2(0.5f), 16, gray);

  alpha = std::abs(std::sin(time / 600));
  font->drawText(u8"Press Enter", screenCenter + Near::Math::Vector2(0, 128), Near::Math::Vector2(0.5f), 32, Near::Math::Color(1.000f, 0.341f, 0.133f, alpha));
}

void TitleScreen::show(){
  visible = true;
  time = 0;
}

void TitleScreen::hide(){
  visible = false;
}
