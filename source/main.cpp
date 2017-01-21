#include <iostream>
#include <string>
#include <fenv.h>
#include "my_opengl.hpp"
#include "main_loop.hpp"
#include "input.hpp"

static inline GLFWwindow *init(Vect<2u, unsigned int> const dim)
{
  if (!glfwInit())
    throw "failed to initialize glfw";
  GLFWwindow *window;

  window = glfwCreateWindow(dim[0], dim[1], "Hello World", glfwGetPrimaryMonitor(), NULL);
  // window = glfwCreateWindow(dim[0], dim[1], "Hello World", NULL, NULL);
  if (!window)
    throw "failed to open window";
  glfwSwapInterval(1);
  glfwMakeContextCurrent(window);
  if (gl3wInit())
    throw "failed to initialize OpenGL";
  if (!gl3wIsSupported(3, 0))
    throw "OpenGL 3.0 not supported";
  return (window);
}

int main(void)
{
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  try
    {
      Vect<2u, unsigned int> dim(1920, 1080);
      // Vect<2u, unsigned int> dim(800, 600);
      GLFWwindow *window = init(dim);
      // should probably be moved to constructor...
      MainLoop mainLoop(dim);

      Callback::setCallbacks(window);

      while (!glfwWindowShouldClose(window))
	{
	  mainLoop.tick();
	  glfwSwapBuffers(window);
	  glfwPollEvents();
	}
    }
  catch (std::string const& e)
    {
      std::cerr << e << std::endl;
      glfwTerminate();
      return (-1);
    }
  return (0);
}
