#ifndef RENDER_TEXTURE_HPP
# define RENDER_TEXTURE_HPP

# include <iostream>
# include "my_opengl.hpp"

class RenderTexture
{
public:
  Framebuffer framebuffer;
  Texture texture;

  RenderTexture(Vect<2u, unsigned int> const size)
    : framebuffer(),
      texture()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size[0], size[1], 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
  
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FALSE)
      {
        std::cout << "TODO: add error for incomplete framebuffer" << std::endl;
      }
  }
};

#endif // !RENDER_TEXTURE_HPP
