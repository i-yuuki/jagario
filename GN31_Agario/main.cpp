#include "pch.h"

#include <NearLib/dialog.h>

#include "game.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' \
  name='Microsoft.Windows.Common-Controls' \
  version='6.0.0.0' \
  processorArchitecture='*' \
  publicKeyToken='6595b64144ccf1df' \
  language='*'\"")

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow){
  std::unique_ptr<Game> game;

  try{
    Near::InitParams initParams;
    initParams.windowTitle = u8"Jagario";
    Near::init(initParams);
    game = std::make_unique<Game>();
    game->init();
  }catch(const std::exception& ex){
    Near::dialog::alert(u8"ゲームを開始できません", std::string(u8"初期化に失敗しました。ゲームファイルが壊れたか、対応していないPCかもしれません。\n\n").append(ex.what()), Near::dialog::DialogIcon::ERROR, u8"ゲームを終了");
    Near::uninit();
    return 1;
  }

  while(!Near::shouldClose()){
    Near::pollEvents();
    game->update();
    game->draw();
  }

  game->uninit();
  game.reset();
  Near::uninit();
  return 0;
}
