#version 130

in vec2 corner;
out vec2 coord;

void main()
{
  coord = corner;
  gl_Position = vec4((corner * 2.0f - vec2(1.0f)), 0.0f, 1.0f);
}