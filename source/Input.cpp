#include <functional>
#include "Input.hpp"

Input Input::instance = Input();

void Input::setWindow(GLFWwindow *window)
{
  // set glfw callback
  glfwSetKeyCallback(window, [] (GLFWwindow *window, int key, int scancode, int action, int mode) {
	  Event ev;
	  ev.hasEvent = true;
	  ev.window = window;
	  ev.type = Event::KEY;
	  ev.val.key = { key, scancode, action, mode };
	  // = { true, Event::KEY, window, {.key = {key, scancode, action, mode}} };
      Input::instance._events.push(ev);
    });
  glfwSetCursorPosCallback(window, [] (GLFWwindow *window, double x, double y) {
	  Event ev;
	  ev.hasEvent = true;
	  ev.window = window;
	  ev.type = Event::MOUSE;
	  ev.val.key = { static_cast<int>(x), static_cast<int>(y) };
	  // Event ev = {true, Event::MOUSE, window, {.mouse = {x, y}}};
      Input::instance._events.push(ev);
    });
  glfwSetMouseButtonCallback(window, [] (GLFWwindow *window, int button, int action, int mods) {
	  Event ev;
	  ev.hasEvent = true;
	  ev.window = window;
	  ev.type = Event::BUTTON;
	  ev.val = { button, action, mods };
	  //Event ev = {true, Event::BUTTON, window, {.button = {button, action, mods}}};
      Input::instance._events.push(ev);
    });
}

Event Input::pollEvent()
{
  if (Input::instance._events.empty())
    {
      Event ev;
      ev.hasEvent = false;
      return ev;
    }

  Event event = Input::instance._events.front();

  Input::instance._events.pop();

  return event;
}
