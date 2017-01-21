#version 130

uniform vec2 offset;
uniform vec2 scale;

in vec2 pos;
in vec3 color;

out vec3 vert_color;

void main()
{
  vert_color = color;
  gl_Position  = vec4((offset + pos) * scale, 0.0f, 1.0f);
}