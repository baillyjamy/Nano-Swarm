#include <iostream>
#include "input.hpp"

Vect<2u, double> Callback::pos(0, 0);
Vect<2u, double> Callback::dragOrigin(0, 0);
bool Callback::leftPressed = false;

void Callback::setCallbacks(GLFWwindow *window)
{
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Callback::mouseCallback(GLFWwindow *window, double x, double y)
{
  (void)window;
  pos = screenToGame({x, y});

  if (leftPressed)
    {
      std::cout << "dragging: x " << pos.x() << ", y " << pos.y() << std::endl;
    }
}

void Callback::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  (void)window;
  (void)mods;
  if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      if (action == GLFW_PRESS)
	{
	  dragOrigin = pos;
	  std::cout << "click at: x " << pos.x() << ", y " << pos.y() << std::endl;
	  leftPressed = true;
	}
      else
	{
	  Vect<2u, double> start(std::min(pos.x(), dragOrigin.x()), std::min(pos.y(), dragOrigin.y()));
	  Vect<2u, double> end(std::max(pos.x(), dragOrigin.x()), std::max(pos.y(), dragOrigin.y()));

	  Logic::getInstance().selectRect(start, end);

	  std::cout << "click release at: x " << pos.x() << ", y " << pos.y() << std::endl;
	  leftPressed = false;
	}
    }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
      std::cout << "Right at: x " << pos.x() << ", y " << pos.y() << std::endl;
    }
}

void Callback::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  (void)window;
  (void)scancode;
  (void)action;
  (void)mode;
  switch (key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, true);
      break;
    }
  std::cout << "key : " << key << std::endl;
}

Vect<2u, double> Callback::screenToGame(Vect<2u, double> pos)
{
  return (pos - Vect<2u, double>(1920 - 1080, 0) * 0.5) / Vect<2u, double>(1080 * 0.5, -1080 * 0.5) + Vect<2u, double>(-1.0, 1.0);
}
