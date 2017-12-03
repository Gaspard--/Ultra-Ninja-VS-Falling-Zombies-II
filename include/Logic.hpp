#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <random>
# include <algorithm>
# include <vector>
# include <memory>
# include <chrono>
# include <mutex>
# include "Entity.hpp"
# include "Input.hpp"
# include "MobManager.hpp"
# include "CityMap.hpp"

class Display;

class Logic
{
private:
  using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
                                 std::chrono::high_resolution_clock,
                                 std::chrono::steady_clock>::type;

  unsigned int time;
  unsigned int score;
  unsigned int combo;
  double multiplier;

  Physics physics;
  MobManager mobManager;
  CityMap cityMap;
  bool gameOver;
  bool running;

  Vect<2u, double> mousePos;

  static constexpr std::chrono::microseconds const getTickTime()
  {
    return std::chrono::microseconds(1000000 / 120);
  };
  std::size_t updatesSinceLastFrame;
  decltype(Clock::now()) lastUpdate;

  void handleKey(GLFWwindow *window, Key key);
  void handleMouse(Display const &, GLFWwindow *window, Mouse mouse);
  void handleButton(GLFWwindow *window, Button button);

public:
  Logic();

  void handleEvent(Display const &, Event const& event);
  void checkEvents(Display const &);
  void update();
  void tick(std::mutex &lock);
  void addToScore(int);
  void resetCombo();
  void incCombo();

  Vect<2, double> getPlayerPos(void) const;
  Vect<2u, double> getMouse(Display const &) const;
  MobManager const& getMobManager() const;
  unsigned int  getScore(void) const;
  std::string   getTime(void) const;
  std::string   getCombo(void) const;
  bool          getGameOver(void) const;

  bool		isRunning() const
  {
    return running;
  }

  bool		&isRunning()
  {
    return running;
  }
};

#endif // !LOGIC_HPP_
