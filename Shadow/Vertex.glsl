#version 330 core
in highp vec4 pos;
in lowp vec3 normal;
in lowp vec4 texcoord;

uniform highp mat4 matrix;
uniform highp mat4 model;

out mediump vec4 outTexc;
out mediump vec3 outNormal;
out mediump vec3 outPos;

void main()
{
  gl_Position =  matrix * model * pos;
  outNormal = transpose(inverse(mat3(model))) * normal;
  outTexc = texcoord;
  outPos = vec3(model * pos);
}
