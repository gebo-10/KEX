#decl


#vert
#version 330
#extension GL_ARB_explicit_uniform_location : enable
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

layout (location = 4) uniform mat4 M;
layout (location = 5) uniform mat4 V;
layout (location = 6) uniform mat4 P;

out vec3 ourColor;

void main()
{
    gl_Position = P*V*M*vec4(position, 1.0f);
    ourColor = color;
}

#frag
#version 330
in vec3 ourColor;
out vec4 color;

void main()
{
    color = vec4(0.5f,0.2f,0.7f, 1.0f);
}