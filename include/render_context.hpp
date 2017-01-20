#ifndef RENDER_CONTEXT_HPP
# define RENDER_CONTEXT_HPP

# include "my_opengl.hpp"

class RenderContext
{
public:
  Vao const vao;
  Program const program;
  //  Vect<TextureCount, GLuint> textures; TODO: textures

  void bind()
  {
    glBindVertexArray(vao);
    glUseProgram(program);
  }

  void unbind()
  {
    glBindVertexArray(0);
    glUseProgram(0);
  }
};

#endif // !RENDER_CONTEXT_HPP
