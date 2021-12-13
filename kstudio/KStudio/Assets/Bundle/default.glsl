#decl


#vert
#version 310 es
precision highp float;

layout(std140, binding = 0) uniform Common
{
    vec4 time;
    vec4 light_dir;
    vec4 ligth_color;
    mat4 V;
    mat4 P;
    mat4 PV;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

layout (location = 0) uniform mat4 M;

void main()
{
    gl_Position = PV*M*vec4(position, 1.0f);
}


#frag
#version 310 es
precision highp float;
out vec4 color;

void main()
{
    //color = vec4(ourColor,1.0f);
    //color = c;
    color=vec4(1.0,0.5,0.3,1.0);
}