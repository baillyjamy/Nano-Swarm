#ifndef MY_OPENGL_HPP_
# define MY_OPENGL_HPP_

# include <string>
# include "GL/gl3w.h"
# include <GLFW/glfw3.h>
# include "vect.hpp"

// these typedefs might be replaced by individual classes down line
typedef GLuint Shader;
typedef GLuint Program;
typedef GLuint Vao;
typedef GLuint glBuffer;
typedef GLuint Framebuffer;
typedef GLuint Texture;

namespace	my_opengl
{
  void		shaderError(GLenum const shadertype, GLuint const shader);
  Shader	createShader(GLenum const shadertype, GLchar const *src);
  void		programError(GLuint const program);
  Vao		createVao();
  glBuffer	createBuffer();
  Framebuffer	createFramebuffer();
  Texture	createTexture();
  void		setUniform(Vect<2, float> const data, char const *target, Program program);
  void		setUniform(int const data, char const *target, Program program);

  template<unsigned int count>
  Program createProgram(Vect<count, Shader const> const shaders)
  {
    Program program(glCreateProgram());
    GLint status;

    for (unsigned int i(0); i < count; ++i)
      glAttachShader(program, shaders[i]);
    glLinkProgram(program);
    for (unsigned int i(0); i < count; ++i)
      glDetachShader(program, shaders[i]);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
      programError(program);
    return (program);
  }

  template<unsigned int count>
  constexpr Program createProgram(Vect<count, GLenum const> const shaderTypes,
				  Vect<count, std::string> const shaderSrcs)
  {
    return (createProgram<count>(Vect<count, const Shader>::applyOp([shaderTypes, shaderSrcs](unsigned int i) {
	    return (createShader(shaderTypes[i], shaderSrcs[i].c_str()));
	  })));
  }
};

#endif // MY_OPENGL_HPP_
