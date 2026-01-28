#version 330 core
in highp vec3 pos;
in lowp vec3 normal;
in lowp vec2 texcoord;

uniform highp mat4 matrix;
uniform highp mat4 model;
uniform highp mat4 lightMatrix;

out mediump vec2 outTexc;
out mediump vec3 outNormal;
out mediump vec3 outPos;
out mediump vec4 outLightSpacePos;

void main()
{
  gl_Position =  matrix * model * vec4(pos, 1.0);
  outNormal = transpose(inverse(mat3(model))) * normal;
  outTexc = texcoord;
  outPos = vec3(model * vec4(pos, 1.0));
  outLightSpacePos = lightMatrix * vec4(outPos, 1.0);
}
