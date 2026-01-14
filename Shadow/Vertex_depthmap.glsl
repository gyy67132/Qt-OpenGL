#version 330 core
in highp vec4 pos;

uniform mat4 lightMatrix;
uniform mat4 model;

void main()
{
  gl_Position = lightMatrix * model * pos;
}
