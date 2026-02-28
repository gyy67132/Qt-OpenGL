#version 330 core

out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D texture;

void main()
{
    //FragColor = texture(texture, texCoord);
    //FragColor = vec4(vec3(1.0 - texture(texture, texCoord)), 1.0);

    FragColor = texture(texture, texCoord);
    float average = (FragColor.r + FragColor.g + FragColor.b)/3.0;
    FragColor = vec4(average, average, average, 1.0);
}
