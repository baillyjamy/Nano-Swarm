#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
#include "display.hpp"
#include "my_opengl.hpp"
#include "bind.hpp"
#include "math.hpp"
#include "logic.hpp"
#include "callback.hpp"
#include "nanobot.hpp"

static inline RenderContext contextFromFiles(std::string name)
{
  std::stringstream vert;
  std::stringstream frag;

  vert << std::ifstream("shaders/" + name + ".vert").rdbuf();
  frag << std::ifstream("shaders/" + name + ".frag").rdbuf();
  return {Vao(), my_opengl::createProgram<2>({GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
					     {vert.str(), frag.str()})};
}

static inline Texture loadNumbers()
{
  Texture texture;
  // Gimp image export
  static struct {
    unsigned       width;
    unsigned       height;
    unsigned       bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    unsigned char  pixel_data[40 * 5 * 4 + 1];
  } numberImage = {
    40, 5, 4,
  "\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0"
  "\377\377\377\377\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377"
  "\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377"
  "\377\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\377\377\377\377"
  "\377\377\377\377\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377"
  "\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377"
  "\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377\377\377\377\377"
  "\377\377\377\377\377\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377"
  "\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377"
  "\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377"
  "\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0"
  "\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\5\377\377\377"
  "\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377"
  "\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377"
  "\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\377"
  "\377\377\377\377\377\377\377\0\0\0\0\377\377\377\377\377\377\377\377\377"
  "\377\377\377\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0"
  "\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377\377"
  "\377\377\377\377\377\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377"
  "\377\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377"
  "\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377\377\377\0\0"
  "\0\0\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377"
  "\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0"
  "\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377"
  "\377\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\0\0\0\0\0\0\0\0\377"
  "\377\377\377\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\0\0"
  "\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377\377\377\377\377\377\377"
  "\377\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0\0\0\377"
  "\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377\377\377\377"
  "\377\377\377\377\377\377\377\0\0\0\0\0\0\0\0\0\0\0\0\377\377\377\377\0\0"
  "\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377\377\377"
  "\377\377\377\377\377\377\377\377\377\0\0\0\0\0\0\0\0\377\377\377\377\0\0"
  "\0\0\0\0\0\0\377\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0\377"
    "\377\377\377\377\377\377\377\377\377\377\377\0\0\0\0",
  };
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
	       0,
	       GL_RGBA8,
	       numberImage.width,
	       numberImage.height,
	       0,
	       GL_RGBA,
	       GL_UNSIGNED_BYTE,
	       static_cast<void *>(numberImage.pixel_data));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}

Display::Display(Vect<2u, unsigned int> size, Logic &logic)
  : size(size), offset{0.0f, 0.0f}, scale{static_cast<float>(size[1]) / static_cast<float>(size[0]), 1.0f},
	  worldRenderContext(contextFromFiles("basic")),
	  lightRenderContext(contextFromFiles("color")),
	  postProcessContext(contextFromFiles("multiply")),
	  hudRenderContext(contextFromFiles("texture")),
	  fixtureBuffer(),
	  lightBuffer(),
	  cornerBuffer(),
	  scoreBuffer(),
	  lightRenderTexture(size),
	  worldRenderTexture(size),
	  numbers(loadNumbers()),
	  fpsCounter(),
	  logic(logic)
  {
    {
      Bind<RenderContext> bind(worldRenderContext);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
      glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), nullptr);
      glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
    }
    {
      Bind<RenderContext> bind(lightRenderContext);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
      glVertexAttribPointer(0, 2, GL_FLOAT, false, 6 * sizeof(float), nullptr);
      glVertexAttribPointer(1, 4, GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
    }
    {
      Bind<RenderContext> bind(postProcessContext);
      float const data[8]{0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 0.0f,
	  1.0f, 1.0f};

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, cornerBuffer);
      glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), data, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
    }
    {
      Bind<RenderContext> bind(hudRenderContext);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, scoreBuffer);
      glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
      glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
    }
  }

Display::~Display()
{
}

void Display::setOffsetAndScale(Program program)
{
  my_opengl::setUniform(offset, "offset", program);
  my_opengl::setUniform(scale, "scale", program);
}

//TODO : optimize
void Display::renderLights()
{
  Bind<RenderContext> bind(lightRenderContext);
  float *data(new float[logic.getLights().size() * 6u  * 3u * 20u]);
  unsigned int i(0);

  std::for_each(logic.getLights().begin(), logic.getLights().end(),
		[&data, &i](Light *l)
		{

		  for (unsigned int j(0); j < 20u; j++)
		    {
		      data[i++] = l->center[0];
		      data[i++] = l->center[1];
		      data[i++] = l->color[0];
		      data[i++] = l->color[1];
		      data[i++] = l->color[2];
		      data[i++] = l->color[3];
		      data[i++] = l->center[0] + cos(static_cast<float>(j) / 20.0f * M_PI * 2.0f) * l->radius;
		      data[i++] = l->center[1] + sin(static_cast<float>(j) / 20.0f * M_PI * 2.0f) * l->radius;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = l->center[0] + cos(static_cast<float>(j + 1) / 20.0f * M_PI * 2.0f) * l->radius;
		      data[i++] = l->center[1] + sin(static_cast<float>(j + 1) / 20.0f * M_PI * 2.0f) * l->radius;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		    }
		});
  glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  setOffsetAndScale(lightRenderContext.program);
  glBindFramebuffer(GL_FRAMEBUFFER, lightRenderTexture.framebuffer);
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 6u);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::renderLasers()
{
  Bind<RenderContext> bind(lightRenderContext);
  float *data(new float[logic.getLasers().size() * 6u * 6u * 2u]);
  unsigned int i(0);

  std::for_each(logic.getLasers().begin(), logic.getLasers().end(),
		[&data, &i](Laser *l)
		{
		  Vect<2u, double> d((l->end - l->start).normalized() * 0.03 * l->power);
		  for (unsigned int a(0); a <= 2u; a += 2)
		    {
		      Vect<2u, double> off(Vect<2u, double>(d[1], -d[0]) * (static_cast<double>(a) - 1.0));

		      for (unsigned int j(0); j < 6u; j++)
			{
			  Vect<2u, double> pos((j & 1 ? l->start : l->end) + (off * (j <= 1 || j == 3)));

			  data[i++] = pos[0];
			  data[i++] = pos[1];
			  data[i++] = !(j <= 1 || j == 3) * 1.0;
			  data[i++] = 2.0;
			  data[i++] = 2.0;
			  data[i++] = !(j <= 1 || j == 3);
			}
		    }
		});
  glBindBuffer(GL_ARRAY_BUFFER, lightBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  setOffsetAndScale(lightRenderContext.program);
  glBindFramebuffer(GL_FRAMEBUFFER, lightRenderTexture.framebuffer);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 6u);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::displayScore(Vect<2u, double> pos, std::string score)
{
  // std::string score("9785634120");
  float *data(new float[score.size() * 4u * 6u]);
  Bind<RenderContext> bind(hudRenderContext);
  constexpr const double width(0.04f);
  constexpr const double height(0.05f);
  unsigned int i(0);

  for (unsigned k(0); k < score.size(); ++k)
    {
      for (unsigned j(0); j < 6u; ++j)
	{
	  data[i++] = (score[k] - '0' + (j & 1u)) * 0.1;
	  data[i++] = !(j <= 1 || j == 3);
	  data[i++] = (k + (j & 1u)) * width + pos[0];
	  data[i++] = (j <= 1 || j == 3) * height + pos[1];
	}
    }
  glBindBuffer(GL_ARRAY_BUFFER, scoreBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, numbers);
  my_opengl::setUniform(0u, "tex", hudRenderContext.program);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 4u);
}

void Display::displayBots()
{
  Bind<RenderContext> bind(worldRenderContext);
  float *data = new float[logic.getNanoBots().size() * 5 * 3];
  unsigned int i(0);

  for (unsigned int j(0); j < logic.getNanoBots().size(); j++)
    {
      NanoBot *n = logic.getNanoBots()[j];
      Vect<2u, double> d(n->getSpeed().normalized() * 0.03);
      Vect<3u, double> colorTip(!n->isAlly() ? Vect<3u, double>{0.0, 0.5, 0.0} :
			     (n->isSelected() ? Vect<3u, double>{1.0, 1.0, 1.0} :
			      Vect<3u, double>{0.0, 1.0, 0.0}));
      Vect<3u, double> color(NanoBot::botColors[n->getType()] * 0.9 + colorTip * 0.1);

      data[i++] = n->getPos()[0] + d[0];
      data[i++] = n->getPos()[1] + d[1];
      data[i++] = color[0];
      data[i++] = color[1];
      data[i++] = color[2];
      data[i++] = n->getPos()[0] + d[1] * 0.5 - d[0];
      data[i++] = n->getPos()[1] - d[0] * 0.5 - d[1];
      data[i++] = color[0];
      data[i++] = color[1];
      data[i++] = color[2];
      data[i++] = n->getPos()[0] - d[1] * 0.5 - d[0];
      data[i++] = n->getPos()[1] + d[0] * 0.5 - d[1];
      data[i++] = color[0];
      data[i++] = color[1];
      data[i++] = color[2];
    }
  glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  setOffsetAndScale(worldRenderContext.program);
  glBindFramebuffer(GL_FRAMEBUFFER, worldRenderTexture.framebuffer);
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 5);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::displayScraps()
{
  Bind<RenderContext> bind(worldRenderContext);
  float *data = new float[logic.getScraps().size() * 6 * 5];
  unsigned int i(0);

  for (unsigned int j(0); j < logic.getScraps().size(); j++)
    {
      Vect<3u, double> color(NanoBot::botColors[logic.getScraps()[j]->getType()]);

      for (unsigned int q(0u); q < 6; ++q)
	{
	  data[i++] = logic.getScraps()[j]->getPos()[0] + ((q <= 1 || q == 3) ? -0.01 : 0.01);
	  data[i++] = logic.getScraps()[j]->getPos()[1] + ((q & 1) ? -0.01 : 0.01);
	  data[i++] = color[0];
	  data[i++] = color[1];
	  data[i++] = color[2];
	}
    }
  glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  setOffsetAndScale(worldRenderContext.program);
  glBindFramebuffer(GL_FRAMEBUFFER, worldRenderTexture.framebuffer);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 5);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::displayMouseSelection()
{
  Bind<RenderContext> bind(worldRenderContext);
  glBindFramebuffer(GL_FRAMEBUFFER, lightRenderTexture.framebuffer);
  if (!Callback::leftPressed)
    return;
  float data[5 * 4];
  unsigned int i(0);

  for (unsigned int j(0); j < 4; j++)
    {
      data[i++] = (j == 1 || j == 2) ? Callback::dragOrigin[0] : Callback::pos[0];
      data[i++] = (j <= 1) ? Callback::dragOrigin[1] : Callback::pos[1];
      data[i++] = 1.0f;
      data[i++] = 1.0f;
      data[i++] = 1.0f;
    }
  glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  setOffsetAndScale(worldRenderContext.program);
  glDrawArrays(GL_LINE_LOOP, 0, 4);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::postProcess()
{
  Bind<RenderContext> bind(postProcessContext);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, lightRenderTexture.texture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, worldRenderTexture.texture);
  my_opengl::setUniform(0u, "lights", postProcessContext.program);
  my_opengl::setUniform(1u, "world", postProcessContext.program);
  my_opengl::setUniform(Vect<2u, float>{1.0f, 1.0f} / Vect<2u, float>(size), "step", postProcessContext.program);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::render()
{
  // lights[0].center += {-0.01, 0.01};
  //  lights[0].center[0] -= 0.01;
  renderLights();
  renderLasers();
  displayMouseSelection();
  displayBots();
  displayScraps();
  postProcess();
  displayScore({-0.9, -0.9}, Logic::getInstance().getScore());
  fpsCounter.tick();
}
