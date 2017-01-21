#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <vector>
# include "my_opengl.hpp"
# include "fixture.hpp"
# include "render_context.hpp"
# include "render_texture.hpp"
# include "light.hpp"
# include "fps_counter.hpp"

class Logic;

class Display
{
private:
  Vect<2u, unsigned int> size;
  Vect<2u, float> offset;
  Vect<2u, float> scale;
  RenderContext const worldRenderContext;
  RenderContext const lightRenderContext;
  RenderContext const frontRenderContext;
  RenderContext const postProcessContext;
  glBuffer fixtureBuffer;
  glBuffer lightBuffer;
  glBuffer cornerBuffer;
  RenderTexture lightRenderTexture;
  RenderTexture worldRenderTexture;
  FPSCounter fpsCounter;
  Logic &logic;

public:
  Display(Vect<2u, unsigned int> size, Logic &logic);
  ~Display();
  void render();
  void setOffsetAndScale(Program program);
  void displayBots();
  void renderLights();
  void postProcess();
  void displayMouseSelection();
};

#endif // !DISPLAY_HPP_
