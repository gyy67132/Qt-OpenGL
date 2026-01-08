#version 330 core
uniform sampler2D texture;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in mediump vec4 outTexc;
in mediump vec3 outNormal;
in mediump vec3 outPos;

out vec4 FragColor;

void main()
{
  vec3 lightColor = vec3(0.8);
  vec3 color = texture(texture, outTexc.st).rgb;

  vec3 normal = normalize(outNormal);
  vec3 lightDir = normalize(lightPos - outPos);
  vec3 eyeDir = normalize(cameraPos - outPos);

  vec3 ambient = 0.3 * lightColor;

  float diff = max(dot(normal, lightDir), 0);
  vec3 diffuse = diff * lightColor ;

  vec3 halfwayDir = normalize(lightDir + eyeDir);
  float spec = pow(max(dot(halfwayDir, normal), 0), 64);
  vec3 specular = spec * lightColor;

  vec3 blendColor = (ambient + diffuse + specular) * color;
  FragColor = vec4(blendColor, 1.0);
}
