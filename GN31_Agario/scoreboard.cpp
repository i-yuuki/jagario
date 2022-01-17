#include "pch.h"
#include "scoreboard.h"

#include <shellapi.h>
#include <NearLib/utils.h>

#include "game.h"

Scoreboard::Scoreboard(Game* game) : GameObject(), game(game){
}

void Scoreboard::init(Near::Layer* layer){
  super::init(layer);

  font = Near::Assets::fonts()->get("Inter");
}

void Scoreboard::draw(){
  std::vector<std::shared_ptr<Player>> players;
  for(auto it : game->getPlayers()){
    players.push_back(it.second);
  }
  std::sort(players.begin(), players.end(), [](auto a, auto b){
    return a->getSize() > b->getSize();
  });
  size_t rows = std::min(size_t{10}, players.size());
  constexpr float rowHeight = 24;

  auto* r = Near::renderer2D();
  r->pushTransform();
  r->setTransform(Near::Math::Matrix::CreateTranslation(transform.position));
  r->setTexture(nullptr);
  r->fillRect(Near::Math::Vector2::Zero, Near::Math::Vector2(200, (rows + 1) * rowHeight), Near::Math::Vector2::Zero, Near::Math::Color(0, 0, 0, 0.5f));
  font->drawText(u8"Scoreboard", Near::Math::Vector2(4, 0.5f * rowHeight), Near::Math::Vector2(0, 0.5f), 16, Near::Math::Color(1, 1, 0, 1));
  for(size_t i = 0;i < rows;i ++){
    font->drawText(std::to_string(i + 1) + u8". " + players[i]->getName(), Near::Math::Vector2(4, (i + 1.5f) * rowHeight), Near::Math::Vector2(0, 0.5f), 16, Near::Math::Color(1, 1, 1, 1));
  }
}
