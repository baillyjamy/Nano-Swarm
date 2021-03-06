#include <iostream>
#include <string>
#include <fenv.h>
#include <SFML/Audio.hpp>
#include "my_opengl.hpp"
#include "main_loop.hpp"
#include "callback.hpp"
#include "music.hpp"

static inline GLFWwindow *init(Vect<2u, unsigned int> const dim)
{
  if (!glfwInit())
    throw "failed to initialize glfw";
  GLFWwindow *window;

  window = glfwCreateWindow(dim[0], dim[1], "Hello World", glfwGetPrimaryMonitor(), NULL);
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
  //  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  try
    {
      Vect<2u, unsigned int> dim(WIDTH, HEIGHT);
      // Vect<2u, unsigned int> dim(800, 600);
      GLFWwindow *window = init(dim);
      // should probably be moved to constructor...
      MainLoop mainLoop(dim);

      Callback::setCallbacks(window);

      Music::getInstance().playMainMusic();
      while (!glfwWindowShouldClose(window))
        {
          if (mainLoop.tick())
            break;
          glfwSwapBuffers(window);
          glfwPollEvents();
        }
    }
  catch (char const *e)
    {
      std::cerr << e << std::endl;
      glfwTerminate();
      return (-1);
    }
  return (0);
}
