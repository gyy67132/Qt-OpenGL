#version 330 core
uniform sampler2D texture;
uniform sampler2D depthTexture;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in mediump vec2 outTexc;
in mediump vec3 outNormal;
in mediump vec3 outPos;
in mediump vec4 outLightSpacePos;

out vec4 FragColor;

float ShadowCalculation(vec4 outLightSpacePos)
{
  //执行透视除法
  vec3 projCoords = outLightSpacePos.xyz / outLightSpacePos.w;
  projCoords = projCoords * 0.5 + 0.5;
  float currentDepth = projCoords.z;
  if(currentDepth > 1.0)
    return 0.0;

  float closestDepth = texture(depthTexture, projCoords.xy).r;

  float shadow = 0.0;
  vec2 texelSize = 1.0 / textureSize(depthTexture, 0);
  for(int x = -1; x <= 1; x++){
    for(int y = -1; y <= 1; y++){
      float closestDepth = texture(depthTexture, projCoords.xy + vec2(x,y)*texelSize).r;
      shadow += currentDepth - 0.005 > closestDepth ? 1 : 0;
    }
  }
  shadow /= 9.0;

  //float shadow = currentDepth - 0.005 > closestDepth ? 1 : 0;
  return shadow;
}

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

  float shaow = ShadowCalculation(outLightSpacePos);
  //vec3 blendColor = (ambient + (diffuse + specular)) * color;
  vec3 blendColor = (ambient + (1.0 - shaow)*(diffuse + specular)) * color;
  FragColor = vec4(blendColor, 1.0);
}
