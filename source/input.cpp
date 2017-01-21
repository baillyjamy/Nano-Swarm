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

void Callback::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  (void)window;
  (void)scancode;
  (void)action;
  (void)mode;
  switch (key)
    {
    case GLFW_KEY_ESCAPE: // Escape close window
      glfwSetWindowShouldClose(window, true);
      break;
    }
  std::cout << "key : " << key << std::endl;
}

void Callback::mouseCallback(GLFWwindow *window, double x, double y)
{
  (void)window;
  pos = {x, y};

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
	  if (dragOrigin == pos)
	    {
	      std::cout << "click release at: x " << pos.x() << ", y " << pos.y() << std::endl;
	    }
	  else
	    {
	      std::cout << "drag release at: x " << pos.x() << ", y " << pos.y() << std::endl;
	    }
	  leftPressed = false;
	}
    }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
      std::cout << "Right at: x " << pos.x() << ", y " << pos.y() << std::endl;
    }
}
