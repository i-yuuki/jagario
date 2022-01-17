#pragma once

#include "packet.h"

class Config{
public:
  Config(const char* path);
  const char* getFilePath();
  void load();
  bool isValid();
  char address[256];
  char playerName[MAX_NAME_LENGTH];
private:
  const char* path;
  bool valid = false;
};
