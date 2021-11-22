#decl


#vert
#version 310 es
precision highp float;

layout(std140, binding = 0) uniform Common
{
    //float time;
    mat4 V;
    mat4 P;
    mat4 PV;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

layout (location = 0) uniform mat4 M;

out vec3 ourColor;

void main()
{
    gl_Position = P*V*M*vec4(position, 1.0f);
    ourColor = color;
}

#frag
#version 300 es
precision highp float;
in vec3 ourColor;
out vec4 color;

void main()
{
    color = vec4(0.5f,0.2f,0.7f, 1.0f);
}