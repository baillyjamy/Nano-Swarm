#version 130

uniform vec2 offset;
uniform vec2 scale;

in vec2 pos;
in vec2 tex;

out vec2 coord;

void main()
{
  coord = tex;
  gl_Position  = vec4((offset + pos) * scale, 0.0f, 1.0f);
}