#version 330 core

out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D textureIn;
uniform int renderFlag;

const float offset = 1.0 / 300.0;

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
    }else if(renderFlag == 4){
        vec2 offsets[9] = vec2[](
            vec2(-offset, offset),
            vec2(0.0, offset),
            vec2(offset, offset),
            vec2(-offset, 0.0),
            vec2(0.0, 0.0),
            vec2(offset, 0.0),
            vec2(-offset, -offset),
            vec2(0.0, -offset),
            vec2(offset, -offset)
        );
        float kernel[9] = float[](
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1);

        vec3 samples[9];
        for(int i = 0; i < 9; i++){
            samples[i] = texture(textureIn, texCoord + offsets[i]).rgb;
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++){
            col += samples[i] * kernel[i];
        }
        FragColor = vec4(col, 1.0);
    }else if(renderFlag == 5){
        vec2 offsets[9] = vec2[](
            vec2(-offset, offset),
            vec2(0.0, offset),
            vec2(offset, offset),
            vec2(-offset, 0.0),
            vec2(0.0, 0.0),
            vec2(offset, 0.0),
            vec2(-offset, -offset),
            vec2(0.0, -offset),
            vec2(offset, -offset)
        );
        float kernel[9] = float[](
            1.0/16, 2.0/16, 1.0/16,
            2.0/16, 4.0/16, 2.0/16,
            1.0/16, 2.0/16, 1.0/16);

        vec3 samples[9];
        for(int i = 0; i < 9; i++){
            samples[i] = texture(textureIn, texCoord + offsets[i]).rgb;
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++){
            col += samples[i] * kernel[i];
        }
        FragColor = vec4(col, 1.0);
    }else if(renderFlag == 6){
        vec2 offsets[9] = vec2[](
            vec2(-offset, offset),
            vec2(0.0, offset),
            vec2(offset, offset),
            vec2(-offset, 0.0),
            vec2(0.0, 0.0),
            vec2(offset, 0.0),
            vec2(-offset, -offset),
            vec2(0.0, -offset),
            vec2(offset, -offset)
        );
        float kernel[9] = float[](
            1.0, 1.0, 1.0,
            1.0, -8.0, 1.0,
            1.0, 1.0, 1.0);

        vec3 samples[9];
        for(int i = 0; i < 9; i++){
            samples[i] = texture(textureIn, texCoord + offsets[i]).rgb;
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++){
            col += samples[i] * kernel[i];
        }
        FragColor = vec4(col, 1.0);
    }
}
