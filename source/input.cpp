//
// input.cpp for input in /home/zeng_d
//
// Made by David Zeng
// Login   <zeng_d@epitech.net>
//
// Started on  Sat Jan 21 00:10:16 2017 David Zeng
// Last update Sat Jan 21 00:10:16 2017 David Zeng
//

#include <iostream>
#include "input.hpp"

double Callback::x = 0;
double Callback::y = 0;
bool Callback::leftPressed = false;

void Callback::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  std::cout << "key : " << key << std::endl;
}

void Callback::mouseCallback(GLFWwindow *window, double x, double y)
{
  Callback::x = x;
  Callback::y = y;

  if (leftPressed)
    {
      std::cout << "dragging at: x " << Callback::x << ", y " << Callback::y << std::endl;
    }
}

void Callback::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      if (action == GLFW_PRESS)
	{
	  std::cout << "Left press at: x " << x << ", y " << y << std::endl;
	  leftPressed = true;
	}
      else
	{
	  std::cout << "Left release at: x " << x << ", y " << y << std::endl;
	  leftPressed = false;
	}
    }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
      std::cout << "Right at: x " << x << ", y " << y << std::endl;
    }
}

void Callback::setCallbacks(GLFWwindow *window)
{
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
}
