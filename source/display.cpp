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
#include "input.hpp"

static inline RenderContext contextFromFiles(std::string name)
{
  std::stringstream vert;
  std::stringstream frag;

  vert << std::ifstream("shaders/" + name + ".vert").rdbuf();
  frag << std::ifstream("shaders/" + name + ".frag").rdbuf();
  return {Vao(), my_opengl::createProgram<2>({GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
					     {vert.str(), frag.str()})};
}

Display::Display(Vect<2u, unsigned int> size, Logic &logic)
  : size(size), offset{0.0f, 0.0f}, scale{static_cast<float>(size[1]) / static_cast<float>(size[0]), 1.0f},
  worldRenderContext(contextFromFiles("basic")),
  lightRenderContext(contextFromFiles("color")),
  postProcessContext(contextFromFiles("multiply")),
  fixtureBuffer(),
  lightBuffer(),
  cornerBuffer(),
  lightRenderTexture(size),
  worldRenderTexture(size),
  lights(),
  fpsCounter(),
  logic(logic)
{
  {
    Bind<RenderContext> bind(worldRenderContext);
    // float const data[12]{0.5f, 0.5f, 1.0f, 0.0f,
    // 	0.0f, -0.7f, 1.0f, 1.0f,
    // 	-0.5f, 0.5f, 0.0f, 1.0f};
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
    //    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), data, GL_STATIC_DRAW);
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
  lights.push_back({{0.5f, 0.0f}, {1.0f, 0.5f, 1.0f, 1.0f}, 1.5f});
  lights.push_back({{-0.5f, 0.0f}, {0.0f, 1.0f, 0.5f, 1.0f}, 0.5f});
}

Display::~Display()
{
  lights.clear();
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
  float *data(new float[lights.size() * 6u  * 3u * 20u]);
  unsigned int i(0);

  std::for_each(lights.begin(), lights.end(),
		[&data, &i](Light l)
		{
		  for (unsigned int j(0); j < 20u; j++)
		    {
		      data[i++] = l.center[0];
		      data[i++] = l.center[1];
		      data[i++] = l.color[0];
		      data[i++] = l.color[1];
		      data[i++] = l.color[2];
		      data[i++] = l.color[3];
		      data[i++] = l.center[0] + cos(static_cast<float>(j) / 20.0f * M_PI * 2.0f) * l.radius;
		      data[i++] = l.center[1] + sin(static_cast<float>(j) / 20.0f * M_PI * 2.0f) * l.radius;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = 0.0f;
		      data[i++] = l.center[0] + cos(static_cast<float>(j + 1) / 20.0f * M_PI * 2.0f) * l.radius;
		      data[i++] = l.center[1] + sin(static_cast<float>(j + 1) / 20.0f * M_PI * 2.0f) * l.radius;
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

void Display::displayBots()
{
  Bind<RenderContext> bind(worldRenderContext);
  float *data = new float[logic.getNanoBots().size() * 4 * 5 * 3];
  unsigned int i(0);

  for (unsigned int j(0); j < logic.getNanoBots().size(); j++)
    {
      Vect<2u, double> d(logic.getNanoBots()[j]->getSpeed().normalized() * 0.01);

      data[i++] = logic.getNanoBots()[j]->getPos()[0] + d[0];
      data[i++] = logic.getNanoBots()[j]->getPos()[1] + d[1];
      data[i++] = 1.0f;
      data[i++] = 1.0f;
      data[i++] = 1.0f;
      data[i++] = logic.getNanoBots()[j]->getPos()[0] + d[1] - d[0];
      data[i++] = logic.getNanoBots()[j]->getPos()[1] - d[0] - d[1];
      data[i++] = 0.0f;
      data[i++] = 1.0f;
      data[i++] = 1.0f;
      data[i++] = logic.getNanoBots()[j]->getPos()[0] - d[1] - d[0];
      data[i++] = logic.getNanoBots()[j]->getPos()[1] + d[0] - d[1];
      data[i++] = 1.0f;
      data[i++] = 0.0f;
      data[i++] = 1.0f;
    }
  glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  delete [] data;
  setOffsetAndScale(worldRenderContext.program);
  glBindFramebuffer(GL_FRAMEBUFFER, worldRenderTexture.framebuffer);
  // glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  // glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLES, 0, i / 5);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_BLEND);
}

void Display::displayMouseSelection()
{
  Bind<RenderContext> bind(worldRenderContext);
  glBindFramebuffer(GL_FRAMEBUFFER, worldRenderTexture.framebuffer);
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (!Callback::leftPressed)
    return;
  float data[4 * 5 * 4];
  unsigned int i(0);

  for (unsigned int j(0); j < 4; j++)
    {
      Vect<2u, double> d(logic.getNanoBots()[j]->getSpeed().normalized() * 0.01);

      data[i++] = (j == 1 || j == 2) ? Callback::dragOrigin[0] : Callback::pos[0];
      data[i++] = (j <= 1) ? Callback::dragOrigin[1] : Callback::pos[1];
      data[i++] = 1.0f;
      data[i++] = 1.0f;
      data[i++] = 1.0f;
    }
  glBindBuffer(GL_ARRAY_BUFFER, fixtureBuffer);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), data, GL_STATIC_DRAW);
  setOffsetAndScale(worldRenderContext.program);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
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
  displayMouseSelection();
  displayBots();
  // TODO : good idea ?
  postProcess();
  fpsCounter.tick();
}
