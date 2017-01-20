#version 130

uniform vec2 offset;
uniform vec2 scale;

in vec2 pos;
in vec4 in_color;

out vec4 vert_color;

void main()
{
  vert_color = in_color;
  gl_Position = vec4((offset + pos) * scale, 0.0f, 1.0f);
}