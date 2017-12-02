# include "GUI.hpp"
# include "Display.hpp"

GUI::Button::Button(const Rect& rect, const std::string str)
  : rect(rect)
  , inactiveColor(rect.color)
  , overflewColor(rect.color)
  , str(str)
{
  overflewColor = Vect<4, float>(inactiveColor[0] * 1.1f,
                                 inactiveColor[1] * 1.1f,
                                 inactiveColor[2] * 1.1f,
                                 inactiveColor[3]);
  for (unsigned int i = 0 ; i < 3 ; i++)
    if (overflewColor[i] > 1)
      overflewColor[i] = 1;
  state = State::INACTIVE;
}

bool GUI::Button::isOverflew(const Vect<2, float>& mouse)
{
  if (mouse.x() >=rect.pos.x() && mouse.x() <=rect.pos.x() +rect.size.x() &&
      mouse.y() >=rect.pos.y() && mouse.y() <=rect.pos.y() +rect.size.y())
    {
      state = State::OVERFLEW;
      return (true);
    }
  state = State::INACTIVE;
  return (false);
}

void GUI::Button::draw(Display& disp)
{
  if (state == State::INACTIVE)
    rect.color =inactiveColor;
  else if (state == State::OVERFLEW)
    rect.color =overflewColor;
  disp.displayRect(rect);
}

void GUI::addElem(const std::string& key, const Button& elem)
{
  stack.insert({key, elem});
}

std::string GUI::haveElemPressed(const Vect<2, float>& mouse, bool leftClick)
{
  for (auto i =stack.begin() ; i !=stack.end() ; ++i)
    if (i->second.isOverflew(mouse) && leftClick)
      return (i->first);
  return ("");
}

void GUI::drawElems(Display& disp)
{
  for (auto i =stack.begin() ; i !=stack.end() ; ++i)
    i->second.draw(disp);
}
