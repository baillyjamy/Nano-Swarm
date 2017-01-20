#include "my_opengl.hpp"
#include <iostream>

void my_opengl::shaderError(GLenum const shadertype, GLuint const shader)
{
  GLint	len;
  GLchar *log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  log = new GLchar[len];
  glGetShaderInfoLog(shader, len, NULL, log);
  std::cout << "Compilation failed for "
	    << ((shadertype == GL_VERTEX_SHADER) ?
		"vertex" : (shadertype == GL_FRAGMENT_SHADER) ?
		"fragment" : "unknown (fix this in my_opengl!)")
	    << " shader:" << std::endl
	    << log << std::endl;
  delete [] log;
  exit(1);
}

void my_opengl::setUniform(Vect<2, float> const data, char const *target, Program program)
{
  glUniform2f(glGetUniformLocation(program, target), data[0], data[1]);
}

void my_opengl::setUniform(int const data, char const *target, Program program)
{
  glUniform1i(glGetUniformLocation(program, target), data);
}

void my_opengl::programError(GLuint const program)
{
  GLint len;
  GLchar *log;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  log = new GLchar[len];
  glGetProgramInfoLog(program, len, NULL, log);
  std::cout << "link failure:" << std::endl
	    << log << std::endl;
  delete [] log;
  exit(1);
}

Shader my_opengl::createShader(GLenum const shadertype, GLchar const *src)
{
  Shader shader(glCreateShader(shadertype));
  GLint status(0);

  glShaderSource(shader, 1, &src, (const GLint  *)0);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    shaderError(shadertype, shader);
  return (shader);
}

Vao my_opengl::createVao()
{
  GLuint vao;

  glGenVertexArrays(1, &vao);
  return (vao);
}

glBuffer my_opengl::createBuffer()
{
  GLuint buffer;

  glGenBuffers(1, &buffer);
  return (buffer);
}

Framebuffer my_opengl::createFramebuffer()
{
  Framebuffer framebuffer;

  glGenFramebuffers(1, &framebuffer);
  return (framebuffer);
}

Texture my_opengl::createTexture()
{
  Texture texture;

  glGenTextures(1, &texture);
  return (texture);
}
