#pragma once

#include <unordered_map>

struct DisplayInfo
{
  std::unordered_map<std::size_t, std::vector<Renderable>> renderables;
  std::string time;
  unsigned int score;
  std::string combo;
  bool gameOver;
};
