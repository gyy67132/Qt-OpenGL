#version 330 core
in highp vec3 pos;

uniform mat4 lightMatrix;
uniform mat4 model;

void main()
{
  gl_Position = lightMatrix * model * vec4(pos, 1.0);
}
