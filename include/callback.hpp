#ifndef CALLBACK_HPP_
# define CALLBACK_HPP_

# include "my_opengl.hpp"
# include "vect.hpp"
# include "logic.hpp"

namespace Callback
{
  void setCallbacks(GLFWwindow *window);

  void mouseCallback(GLFWwindow *window, double x, double y);
  void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
  Vect<2u, double> screenToGame(Vect<2u, double> pos);
  void selectBots();

  // mouse data
  extern Vect<2u, double> pos;
  extern Vect<2u, double> dragOrigin;
  extern bool leftPressed;
  extern bool rightPressed;

  // key data
  extern Vect<4u, bool> keyPressed;
  extern bool spacePressed;
};

#endif /* !CALLBACK_HPP_ */
