#ifndef INPUT_HPP_
# define INPUT_HPP_

# include "my_opengl.hpp"
# include "vect.hpp"
# include "logic.hpp"

namespace Callback
{
  void setCallbacks(GLFWwindow *window);

  void mouseCallback(GLFWwindow *window, double x, double y);
  void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

  // mouse data
  extern Vect<2u, double> pos;

  // original click
  extern bool leftPressed;
  extern Vect<2u, double> dragOrigin;
};

#endif /* !INPUT_HPP_ */
