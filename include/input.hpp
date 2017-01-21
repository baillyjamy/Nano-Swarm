#ifndef INPUT_HPP_
# define INPUT_HPP_

# include "my_opengl.hpp"

class Callback
{
public:
  static void setCallbacks(GLFWwindow *window);

  static void mouseCallback(GLFWwindow *window, double x, double y);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

  // mouse data
  static double x;
  static double y;
  static bool leftPressed;
};

class KeyInput
{
public:
private:
};

class MouseInput
{
public:
private:
};

#endif /* !INPUT_HPP_ */
