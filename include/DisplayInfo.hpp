#pragma once

#include <unordered_map>

struct DisplayInfo
{
  std::unordered_map<GLuint, std::vector<Renderable>> renderables;
  std::vector<Renderable> arrows;
  std::string time;
  long unsigned int score;
  std::string combo;
  unsigned int bomb;
  double ulti;
  bool gameOver;
  bool tutoPage;
};
