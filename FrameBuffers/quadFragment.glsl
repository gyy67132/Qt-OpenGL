#version 330 core

out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D textureIn;
uniform int renderFlag;

void main()
{
    if(renderFlag == 1)
        FragColor = texture(textureIn, texCoord);
    else if(renderFlag == 2)
        FragColor = vec4(vec3(1.0 - texture(textureIn, texCoord)), 1.0);
    else if(renderFlag == 3){
        FragColor = texture(textureIn, texCoord);
        float average = (FragColor.r + FragColor.g + FragColor.b)/3.0;
        FragColor = vec4(average, average, average, 1.0);
    }
}
