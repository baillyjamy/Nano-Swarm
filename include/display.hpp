#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <vector>
# include "my_opengl.hpp"
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
  RenderContext const postProcessContext;
  RenderContext const hudRenderContext;
  glBuffer fixtureBuffer;
  glBuffer lightBuffer;
  glBuffer cornerBuffer;
  glBuffer scoreBuffer;
  RenderTexture lightRenderTexture;
  RenderTexture worldRenderTexture;
  Texture numbers;
  FPSCounter fpsCounter;
  Logic &logic;

public:
  Display(Vect<2u, unsigned int> size, Logic &logic);
  ~Display();
  void render();
  void setOffsetAndScale(Program program);
  void displayBots();
  void displayScraps();
  void displayScore(Vect<2u, double> pos, std::string score);
  void renderLights();
  void renderLasers();
  void postProcess();
  void displayMouseSelection();
};

#endif // !DISPLAY_HPP_
