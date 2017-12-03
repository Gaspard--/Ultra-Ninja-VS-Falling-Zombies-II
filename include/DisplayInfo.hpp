#pragma once

#include <unordered_map>

struct DisplayInfo
{
  std::unordered_map<GLuint, std::vector<Renderable>> renderables;
  std::string time;
  unsigned int score;
  std::string combo;
  unsigned int bomb;
  bool gameOver;
};
