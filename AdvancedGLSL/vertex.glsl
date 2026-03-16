#version 420 core

layout(location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    if(gl_VertexID == 0)
        gl_PointSize = 10;
    else if(gl_VertexID == 1)
        gl_PointSize = 5;
    else if(gl_VertexID == 2)
        gl_PointSize = 15;
    else if(gl_VertexID == 3)
        gl_PointSize = 20;
}
