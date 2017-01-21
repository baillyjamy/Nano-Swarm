#ifndef INPUT_HPP_
# define INPUT_HPP_

# include "my_opengl.hpp"
# include "vect.hpp"

class Callback
{
public:
  static void setCallbacks(GLFWwindow *window);

  static void mouseCallback(GLFWwindow *window, double x, double y);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

  // mouse data
  static Vect<2u, double> pos;

  // original click
  static bool leftPressed;
  static Vect<2u, double> dragOrigin;
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
