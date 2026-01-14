#version 330 core

out vec4 FragColor;

void main()
{
    //float depth = gl_FragCoord.z / gl_FragCoord.w;  // [0,1] 范围
    //FragColor = vec4(vec3(depth), 1.0);  // 可视化深度分布
}
