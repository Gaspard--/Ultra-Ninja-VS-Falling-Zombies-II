#pragma once

struct DisplayInfo
{
  std::vector<Renderable> renderables;
  std::string time;
  unsigned int score;
  std::string combo;
  unsigned int bomb;
  bool gameOver;
};
