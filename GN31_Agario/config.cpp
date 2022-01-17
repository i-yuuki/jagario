#include "pch.h"
#include "config.h"

#include <stdio.h>

Config::Config(const char* path) : path(path){
}

const char* Config::getFilePath(){
  return path;
}

void Config::load(){
  valid = false;
	FILE* f;
  if(fopen_s(&f, path, "r")) return;

  valid = fscanf_s(f, "%s %s", playerName, sizeof(playerName), address, sizeof(address)) == 2;

  fclose(f);
}

bool Config::isValid(){
  return valid;
}