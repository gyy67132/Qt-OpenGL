#version 330 core

out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D textureIn;

void main()
{
    FragColor = texture(textureIn, texCoord);
    //FragColor = vec4(0.2, 0.2, 0.2, 1.0);
}
