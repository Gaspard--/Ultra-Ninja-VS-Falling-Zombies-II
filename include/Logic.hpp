#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <random>
# include <algorithm>
# include <vector>
# include <memory>
# include "Entity.hpp"
# include "Input.hpp"
# include "Player.hpp"

class Display;

class Logic
{
private:
  unsigned int time;
  unsigned int score;
  unsigned int combo;
  double multiplier;

  bool gameOver;

  Vect<2u, float> mousePos;

  void handleKey(GLFWwindow *window, Key key);
  void handleMouse(Display const &, GLFWwindow *window, Mouse mouse);
  void handleButton(GLFWwindow *window, Button button);

public:
  Logic();

  void handleEvent(Display const &, Event const& event);
  void checkEvents(Display const &);
  void tick(void);
  void addToScore(int);
  void resetCombo();
  void incCombo();

  Vect<2, double> getPlayerPos(void) const;
  Vect<2u, float> getMouse(Display const &) const;
  unsigned int  getScore(void) const;
  std::string   getTime(void) const;
  std::string   getCombo(void) const;
  bool          getGameOver(void) const;
};

#endif // !LOGIC_HPP_
