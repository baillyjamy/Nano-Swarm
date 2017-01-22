#include <iostream>
#include "callback.hpp"

Vect<2u, double> Callback::pos(0, 0);
Vect<2u, double> Callback::dragOrigin(0, 0);
bool Callback::leftPressed = false;
bool Callback::rightPressed = false;
Vect<4u, bool> Callback::keyPressed = {false, false, false, false};
bool Callback::spacePressed = false;

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
      selectBots();
    }
  if (rightPressed)
    {
      Logic::getInstance().moveSelection(pos);
    }
}

void Callback::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  (void)window;
  (void)mods;

  // LEFT BUTTON
  if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      if (action == GLFW_PRESS)
	{
	  dragOrigin = pos;
	  leftPressed = true;
	}
      else
	{
	  selectBots();
	  leftPressed = false;
	}
    }

  // RIGHT BUTTON
  else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      if (action == GLFW_PRESS)
	{
	  rightPressed = true;
	  Logic::getInstance().moveSelection(pos);
	}
      else
	{
	  rightPressed = false;
	}
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

    case GLFW_KEY_SPACE:
      if (action == GLFW_PRESS)
	{
	  spacePressed = true;
	  Logic::getInstance().selectAllBots(keyPressed);
	}
      else if (action == GLFW_RELEASE)
	{
	  spacePressed = false;
	}
      break;

    case GLFW_KEY_1 ... GLFW_KEY_4:
      if (action == GLFW_PRESS)
	{
	  keyPressed[key - GLFW_KEY_1] = true;
	}
      else if (action == GLFW_RELEASE)
	{
	  keyPressed[key - GLFW_KEY_1] = false;
	}
      if (leftPressed)
	selectBots();
      else
	Logic::getInstance().refreshSelection(keyPressed);
      break;
    }
}

Vect<2u, double> Callback::screenToGame(Vect<2u, double> pos)
{
  return (pos - Vect<2u, double>(1920 - 1080, 0) * 0.5) / Vect<2u, double>(1080 * 0.5, -1080 * 0.5) + Vect<2u, double>(-1.0, 1.0);
}

void Callback::selectBots()
{
  Vect<2u, double> start(std::min(pos.x(), dragOrigin.x()), std::min(pos.y(), dragOrigin.y()));
  Vect<2u, double> end(std::max(pos.x(), dragOrigin.x()), std::max(pos.y(), dragOrigin.y()));
  Logic::getInstance().selectRect(start, end, keyPressed);
}
