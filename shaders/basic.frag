#version 130

in vec2 coord;
out vec4 color;

void main()
{
  color = vec4(coord, 1.0f, 1.0f);
}