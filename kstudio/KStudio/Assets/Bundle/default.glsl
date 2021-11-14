#decl


#vert
#version 330 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

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
    color = vec4(ourColor, 1.0f);
}