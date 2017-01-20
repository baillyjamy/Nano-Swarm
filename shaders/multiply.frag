#version 130

uniform sampler2D lights;
uniform sampler2D world;
uniform vec2 step;

in vec2 coord;
out vec4 color;

void main()
{
  vec4 world_color = vec4(0);

  for (float i = -1.0f; i < 2.0f; i++)
    for (float j = -1.0f; j < 2.0f; j++)
      world_color += texture(world, clamp(coord + step * vec2(i, j), 0.01f, 0.99f)) * (3.0f - i * i + j * j);
  color = texture(lights, coord) * world_color / 15.0f;
}